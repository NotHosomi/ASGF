#include "include\ASGF\RenderTexture.h"

#include <SDL.h>
#include <exception>
#include <string>

#include "include\ASGF\Camera.h"


RenderTexture::RenderTexture(RenderTexture&& other) noexcept :
	RenderGeneric(std::move(other))
{
	SDL_Texture* temp = other.m_pTexture;
	other.m_pTexture = nullptr;
	std::memcpy(this, &other, sizeof(RenderGeneric));
	this->m_pTexture = temp;
	temp = nullptr;
}

RenderTexture::RenderTexture(const RenderTexture& other) :
	RenderGeneric(other)
{
	std::memcpy(this, &other, sizeof(RenderGeneric));
	this->m_pTexture = nullptr;
}

RenderTexture::~RenderTexture()
{
	m_pTexture = nullptr;
}

void RenderTexture::Free()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
}

void RenderTexture::Render()
{
	if (!m_bVisible) { return; }
	if (m_pTexture == nullptr) { return; }

	SDL_Rect renderQuad = { m_nX, m_nY, m_tClip.w, m_tClip.h };
	Camera* cam = Camera::GetMainCamera();
	if (!m_bCameraLock && cam != nullptr)
	{
		renderQuad.x -= static_cast<int>(cam->GetXOffset());
		renderQuad.y -= static_cast<int>(cam->GetYOffset());
	}
	if (renderQuad.x > ms_nWidth || renderQuad.y > ms_nHeight) { return; }
	if (renderQuad.x + renderQuad.w < 0 || renderQuad.y + renderQuad.h < 0) { return; }

	SDL_Point center(static_cast<int>(m_tPivot.x * m_nWidth), static_cast<int>(m_tPivot.y * m_nHeight));
	Prerender();
	if (SDL_RenderCopyEx(ms_pRenderer, m_pTexture, &m_tClip, &renderQuad, m_fAngle, &center, m_eFlip) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - texture render", SDL_GetError(), nullptr);
		throw std::exception(SDL_GetError());
	}
}

int RenderTexture::GetX()
{
	return m_nX;
}

int RenderTexture::GetY()
{
	return m_nY;
}

WorldCoord RenderTexture::GetPos()
{
	return WorldCoord(m_nX, m_nY);
}

void RenderTexture::SetX(int val)
{
	m_nX = val - static_cast<int>(m_tOrigin.x * m_nWidth);
}

void RenderTexture::SetY(int val)
{
	m_nY = val - static_cast<int>(m_tOrigin.y * m_nHeight);
}

void RenderTexture::SetPos(WorldCoord tPos)
{
	m_nX = tPos.x - static_cast<int>(m_tOrigin.x * m_nWidth);
	m_nY = tPos.y - static_cast<int>(m_tOrigin.y * m_nHeight);
}

int RenderTexture::GetWidth()
{
	return m_nWidth;
}

int RenderTexture::GetHeight()
{
	return m_nHeight;
}

Vector2<int> RenderTexture::GetDims()
{
	return Vector2<int>{m_nWidth, m_nHeight};
}

void RenderTexture::SetWidth(int w)
{
	m_nWidth = w;
}

void RenderTexture::SetHeight(int h)
{
	m_nHeight = h;
}

void RenderTexture::SetDims(Vector2<int> tDims)
{
	m_nWidth = tDims.x;
	m_nHeight = tDims.y;
}

void RenderTexture::SetPivot(Vector2<float> tPivot)
{
	m_tPivot = tPivot;
}

Vector2<float> RenderTexture::GetPivot()
{
	return m_tPivot;
}

void RenderTexture::SetOrigin(Vector2<float> tOrigin)
{
	m_tOrigin = tOrigin;
}

Vector2<float> RenderTexture::GetOrigin()
{
	return m_tOrigin;
}

WorldCoord RenderTexture::GetCenter()
{
	return {m_nX + m_nWidth/2, m_nY + m_nWidth/2};
}

void RenderTexture::SetRotation(float fDegrees)
{
	m_fAngle = fDegrees;
}

float RenderTexture::GetRotation()
{
	return m_fAngle;
}

void RenderTexture::SetFlipState(ASGF::E_FlipState eFlipState)
{
	m_eFlip = static_cast<SDL_RendererFlip>(eFlipState);
}

ASGF::E_FlipState RenderTexture::GetFlipState()
{
	return static_cast<ASGF::E_FlipState>(m_eFlip);
}