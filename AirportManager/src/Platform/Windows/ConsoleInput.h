#pragma once
#include "Core/Input.h"

class ConsoleInput final : public Input
{
public:
	std::string GetSingleWord() override;
};
