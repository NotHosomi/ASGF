#pragma once
#include <chrono>

class Stopwatch
{
public:
	Stopwatch();
	// returns the elapsed time in milliseconds
	unsigned int Peek();
	void Mark();
private:
	std::chrono::system_clock::time_point m_Start;
};

