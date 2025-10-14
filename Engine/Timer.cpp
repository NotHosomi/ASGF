#include "include/ASGF/Timer.h"


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

void Timer::SetDuration(int nMilliseconds)
{
    m_Duration = std::chrono::milliseconds(nMilliseconds);
}

void Timer::SetDurationSecs(float fSeconds)
{
    m_Duration = std::chrono::milliseconds(static_cast<int>(fSeconds * 1000));
}
