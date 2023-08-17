#include "Window.h"
#include <iostream>
#include "Stopwatch.h"
#include "Timer.h"
#include "Texture.h"

Window::Window(int width, int height)
	: m_zWidth(width), m_zHeight(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Error - video subsystem\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - video subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	m_Window = SDL_CreateWindow("MySDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "SDL Error - window creation\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - window creation", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_IMG Error - image subsystem\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_image Error - image subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr)
	{
		std::cout << "SDL Error - renderer creation\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - could not initialize renderer", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}
	Texture::BindRenderer(m_Renderer);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);
}

void Window::LoadAssets()
{
	m_vTextures.emplace_back("HelloWorld.bmp");
	m_vTextures.emplace_back("bg.bmp");
}

void Window::Close()
{
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	// close subsystems
	SDL_Quit();
}

void Window::Loop()
{
	bool quit = false;
	SDL_Event e;
	int frameCount = 0;
	Timer timer;
	timer.SetDuration(1000);
	timer.Start();
	do
	{
		++frameCount;
		if (timer.Elapsed())
		{
			printf("FPS: %d\n", (int)(frameCount));
			frameCount = 0;
		}
		// Input event queue
		while (SDL_PollEvent(&e) != 0)
		{
			//SDL_BlitSurface(m_pCurrentSurface, nullptr, m_ScreenSurface, nullptr);
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		// clear
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_Renderer);

		m_vTextures[0].Render(0, 0);
		m_vTextures[1].Render(78, 400);
		SDL_RenderPresent(m_Renderer);

		const char* err = SDL_GetError();
		if (err != "")
		{
			printf("%s\n", err);
			SDL_ClearError();
		}
		
	} while (!quit);
}