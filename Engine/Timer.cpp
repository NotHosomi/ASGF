#include "include/ASGF/Timer.h"


Timer::Timer()
{
    SetDuration(0);
    Start();
}

Timer::Timer(int nMilliseconds)
{
    SetDuration(nMilliseconds);
	Start();
}

bool Timer::Elapsed()
{
    if (std::chrono::system_clock::now() <= m_EndTime)
        return false;
    m_EndTime = std::chrono::system_clock::now() + m_Duration;
    return true;
}

bool Timer::Peek()
{
    return std::chrono::system_clock::now() > m_EndTime;
}

void Timer::Start()
{
    m_EndTime = std::chrono::system_clock::now() + m_Duration;
}

void Timer::Start(int nMilliseconds)
{
    SetDuration(nMilliseconds);
    Start();
}

void Timer::SetDuration(int nMilliseconds)
{
    m_Duration = std::chrono::milliseconds(nMilliseconds);
}

void Timer::SetDurationSecs(float fSeconds)
{
    m_Duration = std::chrono::milliseconds(static_cast<int>(fSeconds * 1000));
}

void Timer::ExtendDuration(int nMilliseconds)
{
    SetDuration(PeekTime() + nMilliseconds);
    Start();
}

int Timer::PeekTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - std::chrono::system_clock::now()).count();
}

bool Timer::StartOrExtend(int nMilliseconds)
{
    if (Elapsed() || nMilliseconds > PeekTime())
    {
        SetDuration(nMilliseconds);
        Start();
    }
}
