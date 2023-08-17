#pragma once
#include <SDL.h>
#include <string>

class Texture
{
public:
	Texture() = default;
	Texture(std::string sName);
	~Texture();

	bool Load(std::string sName);
	void Free();

	void Render(int x, int y);

	int getWidth();
	int getHeight();

	static void BindRenderer(SDL_Renderer* pRenderer);
private:
	static SDL_Renderer* ms_pRenderer;
	SDL_Texture* m_pTexture = nullptr;
	int m_nWidth = 0;
	int m_nHeight = 0;
};

