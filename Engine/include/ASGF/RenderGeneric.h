#pragma once
#include <SDL.h>

namespace ASGF
{
	enum class E_FlipState
	{
		None,
		Horizontal,
		Vertical
	};
}

class RenderGeneric
{
public:
	static void BindRenderer(SDL_Renderer* pRenderer, int nWindowWidth, int nWindowHeight);

	virtual void Free();
	void Render(SDL_Rect* pClip = nullptr, SDL_Point* center = nullptr);

	void SetVisible(bool bVisibility);
	bool IsVisible();

	int GetX();
	int GetY();
	void SetX(int val);
	void SetY(int val);

	int GetWidth();
	int GetHeight();
	void SetWidth(int w);
	void SetHeight(int h);

	void SetRotation(float fDegrees);
	float GetRotation();

	void SetFlipState(ASGF::E_FlipState eFlipState);
	ASGF::E_FlipState GetFlipState();

	void SetCameraLock(bool bLocked);
	bool GetCameraLock();

protected:
	RenderGeneric() = default;
	RenderGeneric(RenderGeneric&& other)  noexcept;
	// Copy constructor - performs a shallow copy, and clears the new object's texture pointer
	RenderGeneric(const RenderGeneric& other);
	~RenderGeneric();

	virtual void Prerender();

	static SDL_Renderer* ms_pRenderer;
	inline static int ms_nWidth;
	inline static int ms_nHeight;

	SDL_Texture* m_pTexture = nullptr;
	bool m_bVisible = true;
	int m_nX = 0;
	int m_nY = 0;
	int m_nWidth = 0;
	int m_nHeight = 0;
	float m_fAngle = 0;
	SDL_RendererFlip m_eFlip = SDL_FLIP_NONE;
	bool m_bCameraLock = false;
	SDL_Color m_Colour = { 255,255,255,255 };	// alpha may not work, blend mode unspecified
};

