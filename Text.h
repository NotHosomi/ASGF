#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:

	Text(const std::string& sText, TTF_Font* tFont); 	  // TODO: implement
	Text(const std::string& sText);						  // TODO: implement
	Text(const Text& other);							  // TODO: implement
	Text(Text&& other);									  // TODO: implement

	void Free();
	bool SetText(const std::string& sText);
	bool SetFont(TTF_Font* font);
	bool SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	bool Load(const std::string& sText, TTF_Font* tFont, SDL_Color tTextColour = {255, 255, 255, 255});

	void Render();
	void Render(int x, int y, SDL_Rect* pClip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static void BindRenderer(SDL_Renderer* pRenderer);
private:
	static SDL_Renderer* ms_pRenderer;
	SDL_Texture* m_pTexture = nullptr;
	TTF_Font* m_Font = nullptr;
	SDL_Color m_Colour;
	int m_nWidth = 0;
	int m_nHeight = 0;
	std::string m_sText;
};

