#pragma once
#include <SDL.h>
#include <string>

// Up next
// https://lazyfoo.net/tutorials/SDL/15_rotation_and_flipping/index.php



class Texture
{
public:
	Texture() = default;
	Texture(std::string sName);
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	~Texture();

	bool Load(std::string sName);
	void Free();

	void setColour(uint8_t r, uint8_t g, uint8_t b);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	void Render(int x, int y, SDL_Rect* pClip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth();
	int GetHeight();
	void SetWidth(int w);
	void SetHeight(int h);

	static void BindRenderer(SDL_Renderer* pRenderer);
private:
	static SDL_Renderer* ms_pRenderer;
	SDL_Texture* m_pTexture = nullptr;
	int m_nWidth = 0;
	int m_nHeight = 0;
	bool m_bFlipped = false;
	std::string m_sTextureName;
};

