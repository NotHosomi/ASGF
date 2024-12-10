#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include "RenderGeneric.h"
#include "Colour.h"

typedef struct _TTF_Font TTF_Font;

class Text : public RenderGeneric
{
public:

	Text(const std::string& sText, const std::string& sFont, int pt);
	Text(const Text& other);
	Text(Text&& other);
	~Text();

	static void BindRenderer(SDL_Renderer* pRenderer);
	static void LoadFont(const std::string& pRenderer, int pt);
	static void FreeFonts();

	bool SetText(const std::string& sText);
	bool SetFont(const std::string& sFontName, int pt);
	bool SetColour(Colour col, uint8_t a = 255);
	bool SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

private:
	static std::map<std::pair<std::string, int>, TTF_Font*> ms_mFonts;
	TTF_Font* m_pFont = nullptr;
	std::string m_sText;

	bool Generate();
	bool FetchFont(const std::string& sFontName, int pt);
};