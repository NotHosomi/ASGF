#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include "Vector2.h"
#include "RenderTexture.h"
#include "Colour.h"

class Sprite : public RenderTexture
{
public:
	Sprite() = default;
	Sprite(const std::string& sName);
	Sprite(const Sprite& other);
	Sprite(Sprite&& other) noexcept;
	~Sprite() = default;

	void Free() override;

	void SetTexture(const std::string& sName);
	void LoadSpriteSheet(const std::string& sName, int columns, int rows);


	//Set blending (SDL_BLENDMODE_BLEND for alpha)
	void setBlendMode(SDL_BlendMode blending);


	// set Spritesheet frame
	void SetSpriteSheetFrame(uint32_t nX, uint32_t nY = 1);

	// removed unused textures from cache
	static void CleanupCache();
	// removes all textures from cache
	static void FreeCache();
	// removes specific key-value from cache
	static void RemoveFromCache(const std::string& sName);
private:
	void Prerender() override;

	struct T_TextureInfo
	{
		T_TextureInfo() = default;
		~T_TextureInfo() = default;
		SDL_Texture* pTexture = nullptr;
		int nWidth = 0;
		int nHeight = 0;
		size_t nRefs = 0;

		bool bIsSheet = false;
		uint32_t nSheetCols = 1;
		uint32_t nSheetRows = 1;
	};
	static T_TextureInfo* Lookup(const std::string& sName);
	static bool Load(const std::string& sName);
	void Mount(const std::string& sName, T_TextureInfo* tInfo);

	std::string m_sTextureName;

	SDL_Rect m_tClip;

	inline static std::unordered_map<std::string, T_TextureInfo> ms_mTextureCache;
};