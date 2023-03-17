#pragma once

// AirportUtils could go in its own file, but usually you will be using these utils if you are handling airport stuff
namespace AirportUtils
{
	// Define some arbitrary rules about airport ID length
	constexpr std::uint32_t MaxIDLength = 3;
	constexpr std::uint32_t MinIDLength = 3;

	// BitShift is used to be able to combine flags together.
	// if index is 0 it looks like 001
	// if index is 1 it look like 010
	template <std::unsigned_integral T>
	constexpr T BitShift(const T index)
	{
		return static_cast<T>(1) << index;
	}

	// Define various ID errors
	enum class IDErrorFlags : std::uint32_t
	{
		NOT_UPPER_CASE = BitShift(0u),
		TOO_MANY_CHARS = BitShift(1u),
		NOT_ENOUGH_CHARS = BitShift(2u),
		MAX_FLAG = BitShift(3u),
	};

	// Define operator overloads to allow for flag like behaviour
	constexpr IDErrorFlags operator |(const IDErrorFlags lhs, const IDErrorFlags rhs) noexcept
	{
		return static_cast<IDErrorFlags>(static_cast<std::underlying_type_t<IDErrorFlags>>(lhs) | static_cast<std::underlying_type_t<IDErrorFlags>>(rhs));
	}

	inline IDErrorFlags& operator |=(IDErrorFlags& lhs, const IDErrorFlags rhs) noexcept
	{
		return lhs = lhs | rhs;
	}

	// This helper class allows for more intuitave flag behaviour.
	// Without this, to comapre if a flag is enabled you would have to do (setFlags & FLAG1) == FLAG1 rather than just setFlags & FLAG1
	// This was idea and implementation was taken from user Trevor's answer on the question https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>, T>>
	class AutoBool
	{
	public:
		constexpr AutoBool(T val) : m_Val(val) {}

		constexpr operator T() const { return m_Val; }
		constexpr explicit operator bool() const
		{
			return static_cast<std::underlying_type_t<T>>(m_Val) != 0;
		}

	private:
		T m_Val;
	};

	constexpr AutoBool<IDErrorFlags> operator &(const IDErrorFlags lhs, const IDErrorFlags rhs) noexcept
	{
		return static_cast<IDErrorFlags>(static_cast<std::underlying_type_t<IDErrorFlags>>(lhs) & static_cast<std::underlying_type_t<IDErrorFlags>>(rhs));
	}

	inline IDErrorFlags& operator &=(IDErrorFlags& lhs, const IDErrorFlags rhs) noexcept
	{
		return lhs = lhs & rhs;
	}

	constexpr IDErrorFlags operator ~(const IDErrorFlags lhs) noexcept
	{
		return static_cast<IDErrorFlags>(~static_cast<std::underlying_type_t<IDErrorFlags>>(lhs));
	}

	constexpr IDErrorFlags operator ^(const IDErrorFlags lhs, const IDErrorFlags rhs) noexcept
	{
		return static_cast<IDErrorFlags>(static_cast<std::underlying_type_t<IDErrorFlags>>(lhs) ^ static_cast<std::underlying_type_t<IDErrorFlags>>(rhs));
	}

	inline IDErrorFlags& operator ^=(IDErrorFlags& lhs, const IDErrorFlags rhs) noexcept
	{
		return lhs = lhs ^ rhs;
	}

	inline IDErrorFlags ValidateID(const std::string_view airportID)
	{
		IDErrorFlags flags{};

		// This array of functions is the implementation to check the ID relating to the flag defined in IDErrorFlags.
		// Currently using lambdas since they are only small checks but normal functions can be used as well!
		static const std::array<std::function<bool(std::string_view)>, 3> IDErrorFuncs =
		{
			[](const std::string_view airportID) { return !std::ranges::all_of(airportID, [](const char character) { return std::islower(character) == 0; }); },
			[](const std::string_view airportID) { return airportID.size() > MaxIDLength; },
			[](const std::string_view airportID) { return airportID.size() < MaxIDLength; },
		};

		// This helps alert future developers that they have added a new flag to the enum, but not defined the functionality here.
		// This can still be bypassed if a developer only increases the array length but doesn't add a new function to the list.
		// Though this bypass is caught at runtime and will output an error and continue as normal.
		static_assert(IDErrorFlags::MAX_FLAG == static_cast<IDErrorFlags>(BitShift(IDErrorFuncs.size())));

		for(std::size_t i = 0; i < IDErrorFuncs.size(); ++i)
		{
			try
			{
				if(IDErrorFuncs.at(i)(airportID))
				{
					flags |= static_cast<IDErrorFlags>(BitShift(i));
				}
			}
			catch(std::bad_function_call& e)
			{
				// https://en.wikipedia.org/wiki/ANSI_escape_code to add red text to the error message instead of default colour.
				// Runtime handling in case a developer does not add functionality to a newly added flag.
				throw std::logic_error(std::format("\033[31mCaught error {}, please check that each flag in IDErrorFlags has an equivalent function in m_ErrorFunctions.\nThe flag that errored is at index {}.\n\033[0m", e.what(), i));
			}
		}

		return flags;
	}

	// Converts high resolution clock to a system clock (primarily to output a date and time in the style the system currently is running in)
	inline std::chrono::system_clock::time_point HighResolutionClockToSystemClock(const std::chrono::high_resolution_clock::time_point time)
	{
		const auto sysNow = std::chrono::system_clock::now();
		const auto hrNow = std::chrono::high_resolution_clock::now();
		return time_point_cast<std::chrono::system_clock::duration>(time - hrNow + sysNow);
	}
}


class Airport
{
public:
	struct Params
	{
		const std::string_view Identifier{};
		const std::uint32_t Cooldown = 60u;
	};

	explicit Airport(const Params&& params);

	[[nodiscard]] std::string_view GetIdentifier() const { return m_Identifier; }
	[[nodiscard]] std::uint32_t GetCooldown();
	[[nodiscard]] std::uint32_t GetMaxCooldown() const { return m_MaxCooldown; }
	[[nodiscard]] std::chrono::time_point<std::chrono::high_resolution_clock> GetLastArrivalTime() const { return m_LastPlaneArrivalTime; }

	bool RequestLanding();

private:
	std::string_view m_Identifier;
	std::uint32_t m_Cooldown;
	std::uint32_t m_MaxCooldown;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastPlaneArrivalTime{};
};
