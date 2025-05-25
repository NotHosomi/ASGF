#include "include/ASGF/TextBox.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

TextBox::TextBox(const std::string& sFont, int pt, const std::string& sText) :
	Text(sFont, pt)
{
	if (sText != "")
	{
		m_sText = sText;
		Generate();
	}
}

TextBox::~TextBox()
{
	Free();
	m_pFont = nullptr;
}

void TextBox::SetTextWidth(int nWidth)
{
	m_nTextWidth = nWidth;
	Generate();
}

int TextBox::GetTextWidth()
{
	return m_nTextWidth;
}

bool TextBox::Generate()
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(m_pFont, m_sText.c_str(), m_Colour, m_nTextWidth);
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
