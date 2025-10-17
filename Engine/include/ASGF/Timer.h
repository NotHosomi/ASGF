#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	bool Elapsed();
	bool Peek();
	void Start();
	void SetDuration(int nMilliseconds);
	void SetDurationSecs(float fSeconds);
	// returns the number of milliseconds remaining
	int PeekTime();
private:
	std::chrono::system_clock::time_point m_EndTime;
	std::chrono::system_clock::duration m_Duration;
};

