#include "Window.h"
#include <iostream>
#include "Stopwatch.h"
#include "Timer.h"
#include "Texture.h"
#include "Input.h"
#include <vector>
#include "Text.h"

//Texture g_Tex1;
//Texture g_Tex2;
//Texture g_TexCursor;
//Texture g_TexAnim;
const int g_zAnimFrames = 4;
SDL_Rect g_SpriteClips[g_zAnimFrames];
int g_frame = 0;
//Texture g_TextTex;
std::vector<Texture> g_vTex;
std::vector<Text> g_vText;

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
	Text::BindRenderer(m_Renderer);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	Input::Init();
}

void Window::LoadAssets()
{
	g_vTex.emplace_back("Background.png");
	g_vTex.emplace_back("Foo.png");

	g_vText.emplace_back("Hello", "BitCheese", 28);
	g_vText.emplace_back("World", "Arial", 18);
	g_vText[1].SetColour(255, 0, 255);
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

void Window::Loop()
{
	bool quit = false;
	int frameCount = 0;
	Timer timer;
	timer.SetDuration(1000);
	timer.Start();

	struct Vec2 { float x = 0; float y = 0; } guyPos;
	do
	{
		++frameCount;
		if (timer.Elapsed())
		{
			printf("FPS: %d\n", (int)(frameCount));
			frameCount = 0;
		}

		Input::Instance()->ProcessEvents();

		if (Input::Instance()->GetKey(E_Keys::W))
		{
			guyPos.y -= 2;
		}
		if (Input::Instance()->GetKey(E_Keys::S))
		{
			guyPos.y += 2;
		}
		if (Input::Instance()->GetKey(E_Keys::A))
		{
			guyPos.x -= 2;
		}
		if (Input::Instance()->GetKey(E_Keys::D))
		{
			guyPos.x += 2;
		}

		if (Input::Instance()->GetMouseButtonDown(1))
		{
			g_vText[0].SetText("MotherFuck");
		}

		// clear
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_Renderer);

		//g_Tex1.Render(0, 0);
		////g_Tex2.Render(0, 0);
		//
		//++g_frame;
		//g_frame %= (g_zAnimFrames*4);
		//g_TexAnim.Render(0, 0, &g_SpriteClips[g_frame/4]);
		//
		//g_TextTex.Render((m_zWidth - g_TextTex.GetWidth()) / 2, (m_zHeight - g_TextTex.GetHeight()) / 2);
		//g_TexCursor.Render(Input::Instance()->GetMousePos().x - 25, Input::Instance()->GetMousePos().y - 25);
		g_vTex[0].Render(0, 0);
		g_vTex[1].Render(guyPos.x, guyPos.y);

		g_vText[0].Render(50, 0);
		g_vText[1].Render(50, 100);
		SDL_RenderPresent(m_Renderer);
	} while (!Input::Instance()->WishQuit());
}