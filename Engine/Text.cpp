#include "include/ASGF/Text.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include <iostream>

std::map<std::pair<std::string, int>, TTF_Font*> Text::ms_mFonts;

Text::Text(const std::string& sFont, int pt, const std::string& sText)
{
	FetchFont(sFont, pt);
	if (sText != "")
	{
		m_sText = sText;
		Generate();
	}
}

Text::Text(const Text& other)
{
	memcpy(this, &other, sizeof(Text));
	m_pTexture = nullptr;
	Generate();
	m_nWidth = other.m_nWidth;
	m_nHeight = other.m_nHeight;
}

Text::Text(Text&& other)
{
	memcpy(this, &other, sizeof(Text));
	other.m_pTexture = nullptr;
}

Text::~Text()
{
	Free();
	m_pFont = nullptr;
}

void Text::LoadFont(const std::string& sFontName, int pt)
{
	if (ms_mFonts.find({ sFontName, pt }) != ms_mFonts.end())
	{
		// this font is already loaded
		assert(false && "trying to load a font that exists");
		return;
	}

	TTF_Font* pFont = TTF_OpenFont(("C:/Windows/Fonts/" + sFontName + ".TTF").c_str(), pt);
	if (pFont == nullptr)
	{
		pFont = TTF_OpenFont(("Assets/Fonts/" + sFontName + ".TTF").c_str(), pt);
	}
	if (pFont == nullptr)
	{
		std::cout << "TTF Error - Loading font\t" << TTF_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Error - Loading font", TTF_GetError(), nullptr);
		throw std::exception(TTF_GetError());
	}
	ms_mFonts.insert({{ sFontName, pt }, pFont});
}

void Text::FreeFonts()
{
	for (auto& iter : ms_mFonts)
	{
		TTF_CloseFont(iter.second);
		iter.second = nullptr;
	}

}


bool Text::SetText(const std::string& sText)
{
	assert(m_pFont != nullptr && "Tried to set text without a font");
	m_sText = sText;
	return Generate();
}

bool Text::SetFont(const std::string& sFontName, int pt)
{
	FetchFont(sFontName, pt);
	return Generate();
}

void Text::SetColour(const Colour& col)
{
	m_tColour = { col.r, col.g, col.b, m_tColour.a };
	Generate();
}

void Text::SetColour(uint8_t r, uint8_t g, uint8_t b)
{
	m_tColour = { r, g, b, m_tColour.a };
	Generate();
}

void Text::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_tColour = { r, g, b, a };
	Generate();
}

void Text::SetAlpha(Uint8 alpha)
{
}

bool Text::Generate()
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_pFont, m_sText.c_str(), m_tColour);
	if (textSurface == nullptr)
	{
		printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	m_pTexture = SDL_CreateTextureFromSurface(ms_pRenderer, textSurface);
	SDL_FreeSurface(textSurface);
	if (m_pTexture == nullptr)
	{
		printf("Failed to create texture from rendered text! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	TTF_SizeText(m_pFont, m_sText.c_str(), &m_nWidth, &m_nWidth);
	return true;
}

bool Text::FetchFont(const std::string& sFontName, int pt)
{
	bool existed = true;
	auto iter = ms_mFonts.find({ sFontName, pt });
	if (iter == ms_mFonts.end())
	{
		existed = false;
		LoadFont(sFontName, pt);
		iter = ms_mFonts.find({ sFontName, pt });
	}
	m_pFont = iter->second;
	return existed;
}