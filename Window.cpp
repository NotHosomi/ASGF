#include "Window.h"
#include <iostream>
#include "Stopwatch.h"
#include "Timer.h"
#include "Texture.h"

Texture g_Tex1;
Texture g_Tex2;
Texture g_TexAnim;
const int g_zAnimFrames = 4;
SDL_Rect g_SpriteClips[g_zAnimFrames];
int g_frame = 0;

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

	Texture::BindRenderer(m_Renderer);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);
}

void Window::LoadAssets()
{
	g_Tex1.Load("Background.png");
	g_Tex2.Load("Foo.png");
	g_Tex2.setBlendMode(SDL_BLENDMODE_BLEND);

	g_TexAnim.Load("foo_walk_sheet.png");
	for (int i = 0; i < g_zAnimFrames; ++i)
	{
		g_SpriteClips[i].x = i * 64;
		g_SpriteClips[i].y = 0;
		g_SpriteClips[i].w = 64;
		g_SpriteClips[i].h = 205;
	}
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

		g_Tex1.Render(0, 0);
		//g_Tex2.Render(0, 0);
		
		++g_frame;
		g_frame %= (g_zAnimFrames*4);
		g_TexAnim.Render(0, 0, &g_SpriteClips[g_frame/4]);

		//m_vTextures[0].Render(0, 0);
		//m_vTextures[1].Render(78, 400);
		//m_vTextures[2].Render(0, 0);
		SDL_RenderPresent(m_Renderer);
	} while (!quit);
}