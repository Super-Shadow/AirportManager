#pragma once

class Renderer
{
public:
	struct Params
	{
		std::uint32_t Width{1280};
		std::uint32_t Height{720};
	};

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	virtual ~Renderer() = default;

	virtual void DisplayLogo() = 0;
	virtual void DisplayCredits() = 0;

	virtual void DisplayText(std::string_view text) = 0;

	virtual void SetWidth(std::uint32_t width) = 0;
	[[nodiscard]] virtual std::uint32_t GetWidth() const = 0;
	virtual void SetHeight(std::uint32_t height) = 0;
	[[nodiscard]] virtual std::uint32_t GetHeight() const = 0;

	static Renderer* Create(const Params&& params);

protected:
	Renderer() = default;
};
