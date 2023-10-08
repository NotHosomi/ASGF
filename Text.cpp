#include "Text.h"
#include <assert.h>
#include <iostream>

SDL_Renderer* Text::ms_pRenderer = nullptr;
TTF_Font* Text::ms_pDefaultFont = nullptr;

Text::Text(const std::string& sText, const std::string& sFont)
{
	m_sText = sText;
	FetchFont(sFont);
	Generate();
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
}

Text::~Text()
{
	m_pFont = nullptr;
	Free();
}

void Text::BindRenderer(SDL_Renderer* pRenderer)
{
	ms_pRenderer = pRenderer;
}

void Text::LoadFont(const std::string& sFontName, int pt)
{
	if (ms_mFonts.find({ sFontName, pt }) != ms_mFonts.end())
	{
		// this font is already loaded
		assert(false && "trying to load a font that exists");
		return;
	}

	TTF_Font* pFont = TTF_OpenFont(("C:/Windows/Fonts/" + sFontName + ".TTF").c_str(), pt);	// font pt size is the second param
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

void Text::Free()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
	m_sText = "";
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
	return Generate();;
}

bool Text::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_Colour = { r, g, b, a };
	return Generate();
}

void Text::Render(int x, int y, SDL_Rect* pClip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, m_nWidth, m_nHeight };
	if (pClip != nullptr)
	{
		renderQuad.w = pClip->w;
		renderQuad.h = pClip->h;
	}

	if (SDL_RenderCopyEx(ms_pRenderer, m_pTexture, pClip, &renderQuad, angle, center, flip) < 0)
	{
		std::cout << "SDL Error - texture render\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - texture render", SDL_GetError(), nullptr);
		throw std::exception(SDL_GetError());
	}
}

bool Text::Generate()
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_pFont, m_sText.c_str(), m_Colour);
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
	m_nWidth = textSurface->w;
	m_nHeight = textSurface->h;
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
