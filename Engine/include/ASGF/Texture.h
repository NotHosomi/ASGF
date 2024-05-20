#pragma once
#include <string>
#include "RenderGeneric.h"
#include <unordered_map>
#include <optional>

class Texture : public RenderGeneric
{
public:
	Texture() = default;
	Texture(std::string sName);
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	~Texture();

	void SetTexture(const std::string& sName);

	void setColour(uint8_t r, uint8_t g, uint8_t b);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);
private:
	struct T_TextureInfo
	{
		T_TextureInfo() = default;
		~T_TextureInfo() = default;
		SDL_Texture* pTexture = nullptr;
		int nWidth = 0;
		int nHeight = 0;
		size_t nRefs = 0;
	};
	static T_TextureInfo* Lookup(const std::string& sName);
	static bool Load(const std::string& sName);
	void Mount(const std::string& sName, T_TextureInfo* tInfo);

	std::string m_sTextureName;

	inline static std::unordered_map<std::string, T_TextureInfo> ms_mTextureCache;
};