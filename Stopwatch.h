#pragma once
#include <chrono>

class Stopwatch
{
public:
	Stopwatch();
	unsigned int Peek();
	void Mark();
private:
	std::chrono::system_clock::time_point m_Start;
};

