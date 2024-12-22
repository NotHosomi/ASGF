#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <functional>


class Game;

class Window
{
public:
	Window(int width, int height);
	void Run(std::function<void(float)> hUpdateFunc, std::function<void()> hRenderFunc);
	void Close();
	void SetWindowTitle(const std::string& sTitle);

private:
	const int m_zWidth;
	const int m_zHeight;

	SDL_Window* m_Window = nullptr;
	SDL_Surface* m_ScreenSurface = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
};

