#pragma once
#include "Stopwatch.h"
#include "Timer.h"
#include "Text.h"

class Frames
{
	Frames();
public:
	static Frames& _Get();

	void _OnNewFrame();
	void _Render();

	static float DeltaTime();
	static void ShowFps(bool bVisible);
	static void LogFps(bool bLog);

private:
	Stopwatch m_DeltaTimeClock;
	float m_fDeltaTime;
	Timer m_FpsTimer;
	Text m_FpsDisplay;
	int frameCount = 0;
	bool m_bShow = false;
	bool m_bLog = false;

};

