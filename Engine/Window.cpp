#include "include/ASGF/Window.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "include/ASGF/Stopwatch.h"
#include "include/ASGF/Timer.h"
#include "include/ASGF/Sprite.h"
#include "include/ASGF/Input.h"
#include "include/ASGF/Text.h"
#include "include/ASGF/Frames.h"
#include "include/ASGF/Sound.h"
#include "include/ASGF/DeferredCall.h"

Window* Window::ms_pMainWindow = nullptr;

Window* Window::GetMainWindow()
{
	return ms_pMainWindow;
}

Window::Window(int width, int height)
	: m_zWidth(width), m_zHeight(height)
{
	if (ms_pMainWindow == nullptr)
	{
		ms_pMainWindow = this;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL Error - video & audio subsystem\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - video & audio subsystem", SDL_GetError(), nullptr);
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

	// Additional modules
	// Image formats
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_IMG Error - image subsystem\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_image Error - image subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	// Text
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF Error - text subsystem\t" << TTF_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_ttf Error - text subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	// Audio
	 //Initialize SDL
	if (Mix_OpenAudioDevice(44100, MIX_DEFAULT_FORMAT, 2, 2048, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE) < 0)
	{
		std::cout << "SDL_Mixer Error - audio subsystem\t" << Mix_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Mixer Error - audio subsystem", SDL_GetError(), nullptr);
		SDL_ClearError();
		throw;
	}

	RenderGeneric::BindRenderer(m_Renderer, m_zWidth, m_zHeight);

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	Input::Init();
	Sound::Setup();
}

void Window::Run(std::function<void()> hUpdateFunc, std::function<void()> hRenderFunc)
{
	assert(hUpdateFunc != nullptr && hRenderFunc != nullptr && "Please provide the window with update and render functions");
	bool quit = false;


	do
	{
		Frames::_Get()._OnNewFrame();

		Input::Instance()->ProcessEvents();

		hUpdateFunc();
		ASGF::_Internal::ProcessDeferredCalls();

		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(m_Renderer);
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		hRenderFunc();

		Frames::_Get()._Render();
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
	Sprite::FreeCache();
	Sound::FreeCache();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

void Window::SetWindowTitle(const std::string& sTitle)
{
	SDL_SetWindowTitle(m_Window, sTitle.c_str());
}

void Window::SetMainWindow()
{
	ms_pMainWindow = this;
}

void Window::Resize(int width, int height)
{
	// todo: implement, look at SDL_RenderSetLogicalSize
	m_hResizeCallback(width, height);
}

int Window::GetWidth()
{
	return m_zWidth;
}

int Window::GetHeight()
{
	return m_zHeight;
}

void Window::RegisterResizeCallback(std::function<void(int, int)> hOnResize)
{
	m_hResizeCallback = hOnResize;
}
