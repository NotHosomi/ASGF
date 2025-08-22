#include "include/ASGF/Line.h"
#include "include/ASGF/Camera.h"

Line::Line(Vector2<int> tStart, Vector2<int> tEnd)
{
	SetStart(tStart);
	SetEnd(tEnd);
}

void Line::Render()
{
	Camera* cam = Camera::GetMainCamera();
	Vector2<int> tStart = m_tStart;
	Vector2<int> tEnd = m_tEnd;

	if (!m_bCameraLock && cam != nullptr)
	{
		tStart.x -= static_cast<int>(cam->GetXOffset());
		tStart.y -= static_cast<int>(cam->GetYOffset());
		tEnd.x -= static_cast<int>(cam->GetXOffset());
		tEnd.y -= static_cast<int>(cam->GetYOffset());
	}
	if ((tStart.x > ms_nWidth && tEnd.x > ms_nWidth) ||
		(tStart.y > ms_nHeight && tEnd.y > ms_nHeight) ||
		(tStart.x < 0 && tEnd.x < 0) || 
		(tStart.y < 0 && tEnd.y < 0))
	{
		return;
	}


	SDL_SetRenderDrawColor(ms_pRenderer, m_tColour.r, m_tColour.g, m_tColour.b, m_tColour.a);
	SDL_RenderDrawLine(ms_pRenderer, m_tStart.x, m_tStart.y, m_tEnd.x, m_tEnd.y);
}

void Line::SetStart(Vector2<int> tStart)
{
	m_tStart = tStart;
}

Vector2<int> Line::GetStart()
{
	return m_tStart;
}

void Line::SetEnd(Vector2<int> tEnd)
{
	m_tEnd = tEnd;
}

Vector2<int> Line::GetEnd()
{
	return m_tEnd;
}

