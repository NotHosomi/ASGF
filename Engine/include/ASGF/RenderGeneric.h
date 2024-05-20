#pragma once
#include <SDL.h>

class RenderGeneric
{
public:
	~RenderGeneric();


	static void BindRenderer(SDL_Renderer* pRenderer, int nWindowWidth, int nWindowHeight);

	void Free();
	void Render(SDL_Rect* pClip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

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

protected:
	RenderGeneric() = default;
	RenderGeneric(RenderGeneric&& other)  noexcept;
	// Copy constructor - performs a shallow copy, and clears the new object's texture pointer
	RenderGeneric(const RenderGeneric& other);

	static SDL_Renderer* ms_pRenderer;
	inline static int ms_nWidth;
	inline static int ms_nHeight;

	SDL_Texture* m_pTexture = nullptr;
	bool m_bVisible = true;
	int m_nX = 0;
	int m_nY = 0;
	int m_nWidth = 0;
	int m_nHeight = 0;
};

