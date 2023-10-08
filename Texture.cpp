#include "Texture.h"
#include <SDL_image.h>
#include <iostream>


SDL_Renderer* Texture::ms_pRenderer = nullptr;


Texture::Texture(std::string sName)
{
	Load(sName);
}

Texture::Texture(const Texture& other)
{
	Load(other.m_sTextureName);
	m_nHeight = other.m_nHeight;
	m_nWidth = other.m_nWidth;
}

Texture::Texture(Texture&& other) noexcept
{
	memcpy(this, &other, sizeof(Texture));
	other.m_pTexture = nullptr;
}

Texture::~Texture()
{
	Free();
}

bool Texture::Load(std::string sName)
{
	static std::string sDirPrefix = "Sprites/";

	Free();

	sName = sDirPrefix + sName;
	SDL_Surface* rawSurface = IMG_Load(sName.c_str());
	if (rawSurface == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load surface", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		rawSurface = IMG_Load("Sprites/MissingTexture.png");
	}

	//Color key image
	SDL_SetColorKey(rawSurface, SDL_TRUE, SDL_MapRGB(rawSurface->format, 0, 0xFF, 0xFF));


	m_pTexture = SDL_CreateTextureFromSurface(ms_pRenderer, rawSurface);
	m_nWidth = rawSurface->w;
	m_nHeight = rawSurface->h;
	SDL_FreeSurface(rawSurface);
	if (m_pTexture == nullptr)
	{
		std::cout << "SDL Error - Failed to create texture " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to create texture", ("Unable to create texture from " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}
	m_sTextureName = sName.substr(sDirPrefix.size());
	return true;
}

void Texture::Free()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
	m_sTextureName = "";
}

void Texture::setColour(uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetTextureColorMod(m_pTexture, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

void Texture::Render(int x, int y, SDL_Rect* pClip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

int Texture::GetWidth()
{
	return m_nWidth;
}

int Texture::GetHeight()
{
	return m_nHeight;
}

void Texture::SetWidth(int w)
{
	m_nWidth = w;
}

void Texture::SetHeight(int h)
{
	m_nHeight = h;
}

void Texture::BindRenderer(SDL_Renderer* pRenderer)
{
	ms_pRenderer = pRenderer;
}
