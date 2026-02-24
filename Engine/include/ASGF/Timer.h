#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	Timer(int nMilliseconds);
	bool Elapsed();
	bool Peek();
	void Start();
	void Start(int nMilliseconds);
	void SetDuration(int nMilliseconds);
	void SetDurationSecs(float fSeconds);
	void ExtendDuration(int nMilliseconds);
	// returns the number of milliseconds remaining
	int PeekTime();
	// If the value is greater, extend the duration and restart, otherwise just start
	bool StartOrExtend(int nMilliseconds);
private:
	std::chrono::system_clock::time_point m_EndTime;
	std::chrono::system_clock::duration m_Duration;
};

