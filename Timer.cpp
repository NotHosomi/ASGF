#include "Timer.h"


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

void Timer::SetDuration(int nDuration)
{
    m_Duration = std::chrono::milliseconds(nDuration);
}
