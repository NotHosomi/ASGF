#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

class Window
{
public:
	Window(int width, int height);
	bool LoadAssets();
	void Close();

	void Loop();


private:
	enum class SurfaceIndices
	{
		null = -1,
		blank,
		up,
		down,
		left,
		right,
		total
	};
	SDL_Surface* LoadSurface(std::string path, std::string format = "bmp");
	void BlitBackground(SDL_Surface* pSurf);

	const int m_zWidth;
	const int m_zHeight;
	SDL_Renderer* m_Renderer = nullptr;
	SDL_Window* m_Window = nullptr;
	SDL_Surface* m_ScreenSurface = nullptr;

	std::vector<SDL_Surface*> m_vSurfaces;
};

