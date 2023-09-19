#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Texture.h"

class Window
{
public:
	Window(int width, int height);
	void LoadAssets();
	void Close();

	void Loop();

private:
	const int m_zWidth;
	const int m_zHeight;

	SDL_Window* m_Window = nullptr;
	SDL_Surface* m_ScreenSurface = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	// Why does this not work
	std::vector<Texture> m_vTextures;
};

