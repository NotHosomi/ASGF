#include "Window.h"
#include <iostream>
#include "Stopwatch.h"
#include "Timer.h"
#include "Texture.h"
#include "Input.h"

Texture g_Tex1;
Texture g_Tex2;
Texture g_TexCursor;
Texture g_TexAnim;
const int g_zAnimFrames = 4;
SDL_Rect g_SpriteClips[g_zAnimFrames];
int g_frame = 0;
Texture g_TextTex;
TTF_Font* g_tFont = nullptr;

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

	Texture::BindRenderer(m_Renderer);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	Input::Init();
}

void Window::LoadAssets()
{
	g_Tex1.Load("Background.png");
	g_Tex2.Load("Foo.png");
	g_Tex2.setBlendMode(SDL_BLENDMODE_BLEND);
	g_TexCursor.Load("CursorMarker.png");

	g_TexAnim.Load("foo_walk_sheet.png");
	for (int i = 0; i < g_zAnimFrames; ++i)
	{
		g_SpriteClips[i].x = i * 64;
		g_SpriteClips[i].y = 0;
		g_SpriteClips[i].w = 64;
		g_SpriteClips[i].h = 205;
	}


	g_tFont = TTF_OpenFont("Assets/Fonts/BitCheese.TTF", 28);
	SDL_Color textColor = { 0, 0, 0 };
	g_TextTex.LoadText("The quick brown fox is cute", g_tFont, textColor);
}

void Window::Close()
{
	TTF_CloseFont(g_tFont);
	g_tFont = nullptr;

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	// close subsystems
	Input::Close();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::Loop()
{
	bool quit = false;
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

		// clear
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_Renderer);

		g_Tex1.Render(0, 0);
		//g_Tex2.Render(0, 0);
		
		++g_frame;
		g_frame %= (g_zAnimFrames*4);
		g_TexAnim.Render(0, 0, &g_SpriteClips[g_frame/4]);
		
		g_TextTex.Render((m_zWidth - g_TextTex.GetWidth()) / 2, (m_zHeight - g_TextTex.GetHeight()) / 2);
		g_TexCursor.Render(Input::Instance()->GetMousePos().x - 25, Input::Instance()->GetMousePos().y - 25);
		//m_vTextures[0].Render(0, 0);
		//m_vTextures[1].Render(78, 400);
		//m_vTextures[2].Render(0, 0);
		SDL_RenderPresent(m_Renderer);
	} while (!Input::Instance()->WishQuit());
}