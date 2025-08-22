#include <SDL.h>
#include <exception>
#include <string>
#include "include\ASGF\RenderGeneric.h"
#include "include\ASGF\Camera.h"
// compiled one

SDL_Renderer* RenderGeneric::ms_pRenderer = nullptr;

void RenderGeneric::BindRenderer(SDL_Renderer* pRenderer, int nWindowWidth, int nWindowHeight)
{
	ms_pRenderer = pRenderer;
	ms_nWidth = nWindowWidth;
	ms_nHeight = nWindowHeight;
}

void RenderGeneric::SetCameraLock(bool bLocked)
{
	m_bCameraLock = bLocked;
}

bool RenderGeneric::GetCameraLock()
{
	return m_bCameraLock;
}

void RenderGeneric::SetColour(const Colour& col)
{
	m_tColour = { col.r, col.g, col.b, m_tColour.a };
}

void RenderGeneric::SetColour(uint8_t r, uint8_t g, uint8_t b)
{
	m_tColour = { r, g, b, m_tColour.a };
}

void RenderGeneric::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_tColour = { r, g, b, a };
}

void RenderGeneric::SetAlpha(Uint8 alpha)
{
	m_tColour.a = alpha;
}

void RenderGeneric::Prerender()
{
	// base does nothing
}

void RenderGeneric::SetVisible(bool bVisibility)
{
	m_bVisible = bVisibility;
}

bool RenderGeneric::IsVisible()
{
	return m_bVisible;
}
