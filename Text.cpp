#include "Text.h"
#include <assert.h>
#include <iostream>

Text::Text(const std::string& sText, TTF_Font* tFont)
{
	Load(sText, tFont);
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
	assert(m_Font != nullptr && "Tried to set text without a font");
	m_sText = sText;
	return Load(m_sText, m_Font, m_Colour);
}

bool Text::SetFont(TTF_Font* font)
{
	m_Font = font;
	return Load(m_sText, m_Font, m_Colour);
}

bool Text::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_Colour = { r, g, b, a };
	return Load(m_sText, m_Font, m_Colour);
}


bool Text::Load(const std::string& textureText, TTF_Font* tFont, SDL_Color tTextColour)
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(tFont, textureText.c_str(), tTextColour);
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
	m_sText = textureText;
	return true;
}

void Text::Render()
{
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

void Text::BindRenderer(SDL_Renderer* pRenderer)
{
	ms_pRenderer = pRenderer;
}