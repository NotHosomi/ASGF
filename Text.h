#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>

class Text
{
public:

	Text(const std::string& sText, const std::string& sFont, int pt);
	Text(const Text& other);
	Text(Text&& other);
	~Text();

	static void BindRenderer(SDL_Renderer* pRenderer);
	static void LoadFont(const std::string& pRenderer, int pt);
	static void FreeFonts();

	void Free();
	bool SetText(const std::string& sText);
	bool SetFont(const std::string& sFontName, int pt);
	bool SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	void Render(int x, int y, SDL_Rect* pClip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	static SDL_Renderer* ms_pRenderer;
	static std::map<std::pair<std::string, int>, TTF_Font*> ms_mFonts;
	SDL_Texture* m_pTexture = nullptr;
	TTF_Font* m_pFont = nullptr;
	SDL_Color m_Colour = { 255,255,255,255 };
	int m_nWidth = 0;
	int m_nHeight = 0;
	std::string m_sText;

	bool Generate();
	bool FetchFont(const std::string& sFontName, int pt);
};

