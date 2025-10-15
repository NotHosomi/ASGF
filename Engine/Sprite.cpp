#include "include/ASGF/Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <iostream>
#include <algorithm>

Sprite::Sprite(const std::string& sName)
{
	SetTexture(sName);
}

Sprite::Sprite(const Sprite& other) :
	RenderTexture(other)
{
	SetTexture(other.m_sTextureName);
	m_nHeight = other.m_nHeight;
	m_nWidth = other.m_nWidth;
}

Sprite::Sprite(Sprite&& other) noexcept :
	RenderTexture(std::move(other))
{
	memcpy(this, &other, sizeof(Sprite));
	other.m_pTexture = nullptr;
}

void Sprite::Free()
{
	assert(false && "Cannot directly free textures due to cache. Use cache static function instead");
}

void Sprite::SetTexture(const std::string& sName)
{
	T_TextureInfo* pTextureInfo = Sprite::Lookup(sName);
	if (pTextureInfo == nullptr)
	{
		Load(sName);
		pTextureInfo = Sprite::Lookup(sName);
		assert(pTextureInfo != nullptr && "Texture should DEFINITELY exist after a load call");
	}
	Mount(sName, pTextureInfo);
}

void Sprite::LoadSpriteSheet(const std::string& sName, int nColumns, int nRows)
{
	assert(nRows > 1 || nColumns > 1 && "Spritesheet should be larger than 1");
	assert(nRows > 0 && nColumns > 0 && "Spritesheet cannot have a dimension be 0");
	if (Sprite::Lookup(sName) != nullptr)
	{
		assert(!Sprite::Lookup(sName)->bIsSheet && "Cannot load a file as a sprite and a spritesheet simultaneously, use RemoveFromCache");
		return;
	}
	Load(sName);
	T_TextureInfo* pTextureInfo = Sprite::Lookup(sName);
	assert(pTextureInfo != nullptr && "Texture should DEFINITELY exist after a load call");

	pTextureInfo->bIsSheet = true;
	pTextureInfo->nSheetCols = nColumns;
	pTextureInfo->nSheetRows = nRows;
	Mount(sName, pTextureInfo);
	m_tClip.w = pTextureInfo->nWidth / pTextureInfo->nSheetCols;
	m_tClip.h = pTextureInfo->nHeight / pTextureInfo->nSheetRows;
	SetSpriteSheetFrame(0, 0);
}

Sprite::T_TextureInfo* Sprite::Lookup(const std::string& sName)
{
	auto iter = ms_mTextureCache.find(sName);
	if (iter == ms_mTextureCache.end())
		return nullptr;
	return &iter->second;
}

void Sprite::Mount(const std::string& sName, T_TextureInfo* tInfo)
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
	m_tClip = { 0, 0, m_nWidth, m_nHeight };
	tInfo->nRefs++;
}

bool Sprite::Load(const std::string& sName)
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

void Sprite::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void Sprite::SetSpriteSheetFrame(uint32_t nX, uint32_t nY)
{
	T_TextureInfo* pInfo = Sprite::Lookup(m_sTextureName);
	assert(pInfo->bIsSheet == true && "Can't set spritesheet frame of a non-sheet texture");
	assert(pInfo->nSheetCols > nX && pInfo->nSheetRows > nY && "Spritesheet frame out of bounds");
	m_tClip.x = nX * m_tClip.w;
	m_tClip.y = nY * m_tClip.h;
}

void Sprite::CleanupCache()
{
	std::erase_if(ms_mTextureCache,
		[](const auto& info)
		{
			if (info.second.nRefs == 0)
			{
				SDL_DestroyTexture(info.second.pTexture);
				return true;
			}
			return false;
		});
}

void Sprite::FreeCache()
{
	for (auto& info : ms_mTextureCache)
	{
		SDL_DestroyTexture(info.second.pTexture);
	}
	ms_mTextureCache.clear();
}

void Sprite::RemoveFromCache(const std::string& sName)
{
	auto pIter = ms_mTextureCache.find(sName);
	if (pIter == ms_mTextureCache.end()) { return; }
	SDL_DestroyTexture(pIter->second.pTexture);
	ms_mTextureCache.erase(sName);
}

void Sprite::Prerender()
{
	SDL_SetTextureColorMod(m_pTexture, m_tColour.r, m_tColour.g, m_tColour.b);
	SDL_SetTextureAlphaMod(m_pTexture, m_tColour.a);
}
