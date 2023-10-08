#include "RenderGeneric.h"
#include <SDL.h>
#include <exception>

SDL_Renderer* RenderGeneric::ms_pRenderer = nullptr;

RenderGeneric::~RenderGeneric()
{
	Free();
}

void RenderGeneric::BindRenderer(SDL_Renderer* pRenderer)
{
	ms_pRenderer = pRenderer;
}

void RenderGeneric::Free()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
}

void RenderGeneric::Render(SDL_Rect* pClip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (!m_bVisible)
		return;

	SDL_Rect renderQuad = { m_nX, m_nY, m_nWidth, m_nHeight };
	if (pClip != nullptr)
	{
		renderQuad.w = pClip->w;
		renderQuad.h = pClip->h;
	}

	if (SDL_RenderCopyEx(ms_pRenderer, m_pTexture, pClip, &renderQuad, angle, center, flip) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - texture render", SDL_GetError(), nullptr);
		throw std::exception(SDL_GetError());
	}
}

void RenderGeneric::SetVisible(bool bVisibility)
{
	m_bVisible = bVisibility;
}

bool RenderGeneric::IsVisible()
{
	return m_bVisible;
}

int RenderGeneric::GetX()
{
	return m_nX;
}

int RenderGeneric::GetY()
{
	return m_nY;
}

void RenderGeneric::SetX(int val)
{
	m_nX = val;
}

void RenderGeneric::SetY(int val)
{
	m_nY = val;
}

int RenderGeneric::GetWidth()
{
	return m_nWidth;
}

int RenderGeneric::GetHeight()
{
	return m_nHeight;
}

void RenderGeneric::SetWidth(int w)
{
	m_nWidth = w;
}

void RenderGeneric::SetHeight(int h)
{
	m_nHeight = h;
}