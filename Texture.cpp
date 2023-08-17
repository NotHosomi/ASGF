#include "Texture.h"
#include <SDL_image.h>
#include <iostream>


SDL_Renderer* Texture::ms_pRenderer = nullptr;

Texture::Texture(std::string sName)
{
	Load(sName);
}

Texture::~Texture()
{
	Free();
}

bool Texture::Load(std::string sName)
{
	Free();

	sName = "Sprites/" + sName;
	SDL_Surface* rawSurface = IMG_Load(sName.c_str());
	if (rawSurface == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load surface", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}
	m_pTexture = SDL_CreateTextureFromSurface(ms_pRenderer, rawSurface);
	SDL_FreeSurface(rawSurface);
	if (m_pTexture == nullptr)
	{
		std::cout << "SDL Error - Failed to create texture " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to create texture", ("Unable to create texture from " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}

	m_nWidth = rawSurface->w;
	m_nHeight = rawSurface->h;
	return true;
}

void Texture::Free()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
}

void Texture::Render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, m_nWidth, m_nHeight };
	if (SDL_RenderCopy(ms_pRenderer, m_pTexture, nullptr, &renderQuad) < 0)
	{
		std::cout << "SDL Error - texture render\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - texture render", SDL_GetError(), nullptr);
		SDL_ClearError();
	}
}

int Texture::getWidth()
{
	return m_nWidth;
}

int Texture::getHeight()
{
	return m_nHeight;
}

void Texture::BindRenderer(SDL_Renderer* pRenderer)
{
	ms_pRenderer = pRenderer;
}
