#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Stopwatch.h"
#include "Timer.h"
#include "Texture.h"
#include "Input.h"
#include <vector>
#include "Text.h"
#include "Game.h"

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

	// Set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	m_Window = SDL_CreateWindow("MySDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "SDL Error - window creation\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - window creation", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		std::cout << "SDL Error - renderer creation\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - could not initialize renderer", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_IMG Error - image subsystem\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_image Error - image subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF Error - text subsystem\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_ttf Error - text subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	RenderGeneric::BindRenderer(m_Renderer);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	Input::Init();
}

void Window::Run(Game* pGame)
{
	bool quit = false;

	Stopwatch deltaTimeClock;
	deltaTimeClock.Mark();
	float deltaTime = 0;

	int frameCount = 0;
	Timer FpsTimer;
	FpsTimer.SetDuration(1000);
	FpsTimer.Start();
	Text FpsDisplay("0", "Verdana", 28);
	FpsDisplay.SetColour(75, 0, 0);

	do
	{
		++frameCount;
		if (FpsTimer.Elapsed())
		{
			printf("FPS: %d\n", (int)(frameCount));
			FpsDisplay.SetText(std::to_string((int)(frameCount)));
			frameCount = 0;
		}

		deltaTime = static_cast<float>(deltaTimeClock.Peek());
		deltaTimeClock.Mark();

		Input::Instance()->ProcessEvents();

		pGame->Update(deltaTime);

		//SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_Renderer);

		pGame->Render();

		FpsDisplay.Render();
		SDL_RenderPresent(m_Renderer);
	} while (!Input::Instance()->WishQuit());
}

void Window::Close()
{
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	// close subsystems
	Input::Close();
	Text::FreeFonts();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}