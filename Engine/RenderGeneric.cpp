#include "include\ASGF\RenderGeneric.h"
#include <SDL.h>
#include <exception>
#include "include\ASGF\Camera.h"
#include <string>

SDL_Renderer* RenderGeneric::ms_pRenderer = nullptr;

RenderGeneric::~RenderGeneric()
{
	Free();
}

void RenderGeneric::BindRenderer(SDL_Renderer* pRenderer, int nWindowWidth, int nWindowHeight)
{
	ms_pRenderer = pRenderer;
	ms_nWidth = nWindowWidth;
	ms_nHeight = nWindowHeight;
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
	if (m_pTexture == nullptr)
		return;


	SDL_Rect renderQuad = { m_nX, m_nY, m_nWidth, m_nHeight };
	Camera* cam = Camera::GetMainCamera();
	if (cam != nullptr)
	{
		renderQuad.x -= static_cast<int>(cam->GetXOffset());
		renderQuad.y -= static_cast<int>(cam->GetYOffset());
	}
	if (renderQuad.x > ms_nWidth || renderQuad.y > ms_nHeight) // lower bounds frustum check
		return;
	if (pClip != nullptr)
	{
		renderQuad.w = pClip->w;
		renderQuad.h = pClip->h;
	}
	if (renderQuad.x + renderQuad.w < 0 || renderQuad.y + renderQuad.h < 0) // upper bound frustum check
		return;

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

RenderGeneric::RenderGeneric(RenderGeneric&& other) noexcept
{
	SDL_Texture* temp = other.m_pTexture;
	other.m_pTexture = nullptr;
	std::memcpy(this, &other, sizeof(RenderGeneric));
	this->m_pTexture = temp;
	temp = nullptr;
}

RenderGeneric::RenderGeneric(const RenderGeneric& other)
{
	std::memcpy(this, &other, sizeof(RenderGeneric));
	this->m_pTexture = nullptr;
}
