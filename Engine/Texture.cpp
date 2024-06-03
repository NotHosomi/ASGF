#include "include/ASGF/Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <iostream>

Texture::Texture(std::string sName)
{
	Load(sName);
}

Texture::Texture(const Texture& other) :
	RenderGeneric(other)
{
	Load(other.m_sTextureName);
	m_nHeight = other.m_nHeight;
	m_nWidth = other.m_nWidth;
}

Texture::Texture(Texture&& other) noexcept :
	RenderGeneric(std::move(other))
{
	memcpy(this, &other, sizeof(Texture));
	other.m_pTexture = nullptr;
}

Texture::~Texture()
{
	Free();
	m_sTextureName = "";
}

void Texture::SetTexture(const std::string& sName)
{
	T_TextureInfo* pTextureInfo = Texture::Lookup(sName);
	if (pTextureInfo == nullptr)
	{
		Load(sName);
		pTextureInfo = Texture::Lookup(sName);
		assert(pTextureInfo != nullptr && "Texture should DEFINITELY exist after a load call");
	}
	Mount(sName, pTextureInfo);
}

Texture::T_TextureInfo* Texture::Lookup(const std::string& sName)
{
	auto iter = ms_mTextureCache.find(sName);
	if (iter == ms_mTextureCache.end())
		return nullptr;
	return &iter->second;
}

void Texture::Mount(const std::string& sName, T_TextureInfo* tInfo)
{
	if (m_sTextureName != "")
	{
		auto iter = ms_mTextureCache.find(m_sTextureName);
		if (iter != ms_mTextureCache.end())
		{
			--(iter->second.nRefs);
		}
	}

	m_sTextureName = sName;
	m_pTexture = tInfo->pTexture;
	m_nHeight = tInfo->nHeight;
	m_nWidth = tInfo->nWidth;
	tInfo->nRefs++;
}

bool Texture::Load(const std::string& sName)
{
	static std::string sDirPrefix = "Assets/Sprites/";

	std::string sFileAddr = sDirPrefix + sName;
	SDL_Surface* rawSurface = IMG_Load(sFileAddr.c_str());
	if (rawSurface == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load surface", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		rawSurface = IMG_Load("Sprites/MissingTexture.png");
	}

	//Color key image
	SDL_SetColorKey(rawSurface, SDL_TRUE, SDL_MapRGB(rawSurface->format, 0, 0xFF, 0xFF));

	T_TextureInfo info;
	info.pTexture = SDL_CreateTextureFromSurface(ms_pRenderer, rawSurface);
	info.nWidth = rawSurface->w;
	info.nHeight = rawSurface->h;
	SDL_FreeSurface(rawSurface);
	if (info.pTexture == nullptr)
	{
		std::cout << "SDL Error - Failed to create texture " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to create texture", ("Unable to create texture from " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}
	ms_mTextureCache.insert({ sName, info });
	return true;
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