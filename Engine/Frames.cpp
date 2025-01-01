#include "include/ASGF/Frames.h"
#include "include/ASGF/Camera.h"

Frames::Frames() :
	m_FpsDisplay("0", "Verdana", 28)
{
	m_DeltaTimeClock.Mark();
	float deltaTime = 0;

	m_FpsTimer.SetDuration(1000);
	m_FpsTimer.Start();
	
	m_FpsDisplay.SetColour(75, 0, 0);
}

Frames& Frames::_Get()
{
	static Frames instance;
	return instance;
}

void Frames::_OnNewFrame()
{
	++frameCount;
	if (m_FpsTimer.Elapsed())
	{
		if (m_bLog)
		{
			printf("FPS: %d\n", (int)(frameCount));
		}
		m_FpsDisplay.SetText(std::to_string((int)(frameCount)));
		frameCount = 0;
	}

	m_fDeltaTime = static_cast<float>(m_DeltaTimeClock.Peek()) / 1000.0f;
	m_DeltaTimeClock.Mark();
}

void Frames::_Render()
{
	if (!m_bShow) { return; }
	if (Camera::GetMainCamera() != nullptr)
	{
		m_FpsDisplay.SetX(static_cast<int>(Camera::GetMainCamera()->GetXOffset()) + 2);
		m_FpsDisplay.SetY(Camera::GetMainCamera()->GetYOffset() + 2);
	}
	m_FpsDisplay.Render();
}

float Frames::DeltaTime()
{
	return _Get().m_fDeltaTime;
}

void Frames::ShowFps(bool bVisible)
{
	_Get().m_bShow = bVisible;
}

void Frames::LogFps(bool bLog)
{
	_Get().m_bLog = bLog;
}
