#include "ampch.h"
#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer(const Params& params) : m_ConsoleWindow(GetConsoleWindow())
{
	SetWidth(params.Width);
	SetHeight(params.Height);
}

void ConsoleRenderer::DisplayLogo()
{
	std::cout << R"(    :::     ::::::::::: :::::::::  :::::::::   ::::::::  :::::::::  :::::::::::       ::::    ::::      :::     ::::    :::     :::      ::::::::  :::::::::: ::::::::: 
  :+: :+:       :+:     :+:    :+: :+:    :+: :+:    :+: :+:    :+:     :+:           +:+:+: :+:+:+   :+: :+:   :+:+:   :+:   :+: :+:   :+:    :+: :+:        :+:    :+: 
 +:+   +:+      +:+     +:+    +:+ +:+    +:+ +:+    +:+ +:+    +:+     +:+           +:+ +:+:+ +:+  +:+   +:+  :+:+:+  +:+  +:+   +:+  +:+        +:+        +:+    +:+ 
+#++:++#++:     +#+     +#++:++#:  +#++:++#+  +#+    +:+ +#++:++#:      +#+           +#+  +:+  +#+ +#++:++#++: +#+ +:+ +#+ +#++:++#++: :#:        +#++:++#   +#++:++#:  
+#+     +#+     +#+     +#+    +#+ +#+        +#+    +#+ +#+    +#+     +#+           +#+       +#+ +#+     +#+ +#+  +#+#+# +#+     +#+ +#+   +#+# +#+        +#+    +#+ 
#+#     #+#     #+#     #+#    #+# #+#        #+#    #+# #+#    #+#     #+#           #+#       #+# #+#     #+# #+#   #+#+# #+#     #+# #+#    #+# #+#        #+#    #+# 
###     ### ########### ###    ### ###         ########  ###    ###     ###           ###       ### ###     ### ###    #### ###     ###  ########  ########## ###    ###)" << "\n\n";
}

void ConsoleRenderer::DisplayCredits()
{
	std::cout << R"(:::::::::  :::   :::       :::::::::  :::::::::: ::::    :::       ::::    ::::   ::::::::  :::::::::      :::     ::::    ::: 
:+:    :+: :+:   :+:       :+:    :+: :+:        :+:+:   :+:       +:+:+: :+:+:+ :+:    :+: :+:    :+:   :+: :+:   :+:+:   :+: 
+:+    +:+  +:+ +:+        +:+    +:+ +:+        :+:+:+  +:+       +:+ +:+:+ +:+ +:+    +:+ +:+    +:+  +:+   +:+  :+:+:+  +:+ 
+#++:++#+    +#++:         +#++:++#+  +#++:++#   +#+ +:+ +#+       +#+  +:+  +#+ +#+    +:+ +#++:++#:  +#++:++#++: +#+ +:+ +#+ 
+#+    +#+    +#+          +#+    +#+ +#+        +#+  +#+#+#       +#+       +#+ +#+    +#+ +#+    +#+ +#+     +#+ +#+  +#+#+# 
#+#    #+#    #+#          #+#    #+# #+#        #+#   #+#+#       #+#       #+# #+#    #+# #+#    #+# #+#     #+# #+#   #+#+# 
#########     ###          #########  ########## ###    ####       ###       ###  ########  ###    ### ###     ### ###    ####)" << "\n\n";
}

void ConsoleRenderer::DisplayText(const std::string_view text)
{
	std::cout << text;
}

void ConsoleRenderer::SetWidth(const std::uint32_t width)
{
	RECT consoleRect;
	GetWindowRect(m_ConsoleWindow, &consoleRect); // stores the console's current dimensions
	MoveWindow(m_ConsoleWindow, consoleRect.left, consoleRect.top, width, GetHeight(), TRUE);
}

std::uint32_t ConsoleRenderer::GetWidth() const
{
	RECT consoleRect;
	GetWindowRect(m_ConsoleWindow, &consoleRect);
	return consoleRect.right - consoleRect.left;
}

void ConsoleRenderer::SetHeight(const std::uint32_t height)
{
	RECT consoleRect;
	GetWindowRect(m_ConsoleWindow, &consoleRect);
	MoveWindow(m_ConsoleWindow, consoleRect.left, consoleRect.top, GetWidth(), height, TRUE);
}

std::uint32_t ConsoleRenderer::GetHeight() const
{
	RECT consoleRect;
	GetWindowRect(m_ConsoleWindow, &consoleRect);
	return consoleRect.bottom - consoleRect.top;
}
