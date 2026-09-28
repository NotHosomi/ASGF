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

	Camera* cam = Camera::GetMainCamera();
	// todo: test cam scaling
	float camScale = (cam == nullptr) ? 1 : cam->GetScale();
	SDL_Rect renderQuad = { 
		static_cast<int>(m_nX),
		static_cast<int>(m_nY),
		static_cast<int>(m_tClip.w * camScale * m_fScaleX),
		static_cast<int>(m_tClip.h * camScale * m_fScaleY) };
	if (!m_bCameraLock && cam != nullptr)
	{
		renderQuad.x -= static_cast<int>(cam->GetXOffset());
		renderQuad.y -= static_cast<int>(cam->GetYOffset());
	}
	renderQuad.x *= camScale;
	renderQuad.y *= camScale;
	if (renderQuad.x > ms_nWidth || renderQuad.y > ms_nHeight) { return; }
	if (renderQuad.x + renderQuad.w < 0 || renderQuad.y + renderQuad.h < 0) { return; }

	SDL_Point center(static_cast<int>(m_tPivot.x * GetWidth()), static_cast<int>(m_tPivot.y * GetHeight()));
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
	m_nX = val - static_cast<int>(m_tOrigin.x * GetWidth());
}

void RenderTexture::SetY(int val)
{
	m_nY = val - static_cast<int>(m_tOrigin.y * GetHeight());
}

void RenderTexture::SetPos(WorldCoord tPos)
{
	m_nX = tPos.x - static_cast<int>(m_tOrigin.x * GetWidth());
	m_nY = tPos.y - static_cast<int>(m_tOrigin.y * GetHeight());
}

int RenderTexture::GetWidth()
{
	return static_cast<int>(m_tClip.w * m_fScaleX);
}

int RenderTexture::GetHeight()
{
	return static_cast<int>(m_tClip.h * m_fScaleY);
}

Vector2<int> RenderTexture::GetDims()
{
	return Vector2<int>{GetWidth(), GetHeight()};
}

void RenderTexture::SetWidth(int w)	// new width/height setting could lead to 1 pixel inaccurary?
{
	m_fScaleX = static_cast<float>(w) / static_cast<float>(m_tClip.w);
}

void RenderTexture::SetHeight(int h)
{
	m_fScaleY = static_cast<float>(h) / static_cast<float>(m_tClip.h);
}

void RenderTexture::SetScaleX(float x)
{
	m_fScaleX = x;
}

void RenderTexture::SetScaleY(float y)
{
	m_fScaleY = y;
}

void RenderTexture::SetDims(Vector2<int> tDims)
{
	SetWidth(tDims.x);
	SetHeight(tDims.y);
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
	return {m_nX + GetWidth() /2, m_nY + GetHeight() /2};
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