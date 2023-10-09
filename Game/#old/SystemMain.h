#pragma once
class SystemMain
{
public:
	SystemMain() = default;
	~SystemMain() = default;

	bool initialize() const;
	void main() const;
	void finalize() const;
};

