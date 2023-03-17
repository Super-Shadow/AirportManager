#include "ampch.h"
#include "Airport.h"

Airport::Airport(const Params&& params) : m_Identifier(params.Identifier), m_Cooldown(0), m_MaxCooldown(params.Cooldown)
{
	// Runtime check to ensure ID is valid.
	// https://en.wikipedia.org/wiki/ANSI_escape_code to add red text to the error message instead of default colour.
	if(static_cast<std::underlying_type_t<AirportUtils::IDErrorFlags>>(AirportUtils::ValidateID(m_Identifier)) != 0)
		throw std::logic_error(std::format("\033[31mAirport Identifier ( {} ) does not pass validation!\n\033[0m", m_Identifier).c_str());
}

std::uint32_t Airport::GetCooldown()
{
	if(m_Cooldown == 0)
		return m_Cooldown;

	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto timeDelta = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_LastPlaneArrivalTime).count();

	if(timeDelta >= m_MaxCooldown)
	{
		m_Cooldown = 0;
	}
	else
		m_Cooldown = m_MaxCooldown - static_cast<std::uint32_t>(timeDelta);

	return m_Cooldown;
}

bool Airport::RequestLanding()
{
	if(GetCooldown() == 0)
	{
		m_LastPlaneArrivalTime = std::chrono::high_resolution_clock::now();
		m_Cooldown = m_MaxCooldown;
		return true;
	}
	return false;
}
