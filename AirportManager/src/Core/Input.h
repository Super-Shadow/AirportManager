#pragma once

class Input
{
public:
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	Input(Input&&) = delete;
	Input& operator=(Input&&) = delete;

	virtual ~Input() = default;

	virtual std::string GetSingleWord() = 0;

	static Input* Create();

protected:
	Input() = default;
};
