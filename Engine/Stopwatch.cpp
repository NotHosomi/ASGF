#include "include/ASGF/Stopwatch.h"

Stopwatch::Stopwatch()
{
	m_Start = std::chrono::system_clock::now();
}

unsigned int Stopwatch::Peek()
{
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_Start).count());
}

void Stopwatch::Mark()
{
	m_Start = std::chrono::system_clock::now();
}
