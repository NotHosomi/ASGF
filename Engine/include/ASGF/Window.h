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
	static Window* GetMainWindow();

	Window(int width, int height);
	void Run(std::function<void()> hUpdateFunc, std::function<void()> hRenderFunc);
	void Close();
	void SetWindowTitle(const std::string& sTitle);

	void SetMainWindow();

	int GetWidth();
	int GetHeight();

private:
	static Window* ms_pMainWindow;

	const int m_zWidth;
	const int m_zHeight;

	SDL_Window* m_Window = nullptr;
	SDL_Surface* m_ScreenSurface = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
};

