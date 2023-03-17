#pragma once
#include "Core/Renderer.h"

class ConsoleRenderer final : public Renderer
{
public:
	explicit ConsoleRenderer(const Params& params);

	ConsoleRenderer(const ConsoleRenderer&) = delete;
	ConsoleRenderer& operator=(const ConsoleRenderer&) = delete;

	ConsoleRenderer(ConsoleRenderer&&) = delete;
	ConsoleRenderer& operator=(ConsoleRenderer&&) = delete;

	~ConsoleRenderer() override = default;

	void DisplayLogo() override;
	void DisplayCredits() override;

	void DisplayText(std::string_view text) override;

	void SetWidth(std::uint32_t width) override;
	[[nodiscard]] std::uint32_t GetWidth() const override;
	void SetHeight(std::uint32_t height) override;
	[[nodiscard]] std::uint32_t GetHeight() const override;

private:
	HWND m_ConsoleWindow;
};
