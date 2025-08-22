#pragma once
#include <SDL.h>
#include "Colour.h"

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

	virtual void Render() = 0;

	void SetVisible(bool bVisibility);
	bool IsVisible();

	void SetCameraLock(bool bLocked);
	bool GetCameraLock();

	virtual void SetColour(const Colour& col);
	virtual void SetColour(uint8_t r, uint8_t g, uint8_t b);
	virtual void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	virtual void SetAlpha(Uint8 alpha);

protected:
	RenderGeneric() = default;
	RenderGeneric(RenderGeneric&& other) = default;
	RenderGeneric(const RenderGeneric& other) = default;
	~RenderGeneric() = default;

	virtual void Prerender();

	static SDL_Renderer* ms_pRenderer;
	inline static int ms_nWidth;
	inline static int ms_nHeight;

	bool m_bVisible = true;
	bool m_bCameraLock = false;
	SDL_Color m_tColour = { 255,255,255,255 };	// alpha may not work, blend mode unspecified
};

