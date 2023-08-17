#pragma once
#include <chrono>

class Timer
{
public:
	bool Elapsed();
	bool Peek();
	void Start();
	void SetDuration(int nDuration);
private:
	std::chrono::system_clock::time_point m_EndTime;
	std::chrono::system_clock::duration m_Duration;
};

