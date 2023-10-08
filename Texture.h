#pragma once
#include <SDL.h>
#include <string>
#include "RenderGeneric.h"
// Up next
// https://lazyfoo.net/tutorials/SDL/15_rotation_and_flipping/index.php



class Texture : public RenderGeneric
{
public:
	Texture() = default;
	Texture(std::string sName);
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	~Texture();

	bool Load(std::string sName);
	void Free();

	void setColour(uint8_t r, uint8_t g, uint8_t b);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);
private:
	std::string m_sTextureName;
};

