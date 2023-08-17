#include "Window.h"
#include <iostream>

Window::Window(int width, int height)
	: m_zWidth(width), m_zHeight(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Error - video subsystem\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - could not initialize video subsystem", SDL_GetError(), nullptr);
		throw;
	}

	m_Window = SDL_CreateWindow("MySDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "SDL Error - window creation\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error - window creation", SDL_GetError(), nullptr);
		throw;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_IMG Error - image subsystem\t" << IMG_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_image Error - could not initialize png image subsystem", SDL_GetError(), nullptr);
		throw;
	}

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);
}

bool Window::LoadAssets()
{
	m_vSurfaces.push_back(LoadSurface("Blank"));
	m_vSurfaces.push_back(LoadSurface("Up"));
	m_vSurfaces.push_back(LoadSurface("Down"));
	m_vSurfaces.push_back(LoadSurface("Left"));
	m_vSurfaces.push_back(LoadSurface("Right"));
	m_vSurfaces.push_back(LoadSurface("bg"));
	m_vSurfaces.push_back(LoadSurface("HelloWorld", "png"));
	return true;
}

void Window::Close()
{
	for (auto& s : m_vSurfaces)
	{
		SDL_FreeSurface(s);
		s = nullptr;
	}
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	// close subsystems
	SDL_Quit();
}

void Window::Loop()
{
	bool quit = false;
	SDL_Event e;
	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::blank];
	do
	{
		BlitBackground(m_vSurfaces.back());
		while (SDL_PollEvent(&e) != 0)
		{
			//SDL_BlitSurface(m_pCurrentSurface, nullptr, m_ScreenSurface, nullptr);
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			{
				//switch (e.key.keysym.sym)
				//{
				//case SDLK_w:
				//	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::up];
				//	break;
				//case SDLK_s:
				//	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::down];
				//	break;
				//case SDLK_a:
				//	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::left];
				//	break;
				//case SDLK_d:
				//	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::right];
				//	break;
				//default:
				//	m_pCurrentSurface = m_vSurfaces[(int)SurfaceIndices::blank];
				//	break;
				//}
				SDL_UpdateWindowSurface(m_Window);
			}
		}
	} while (!quit);
}

SDL_Surface* Window::LoadSurface(std::string sName, std::string sFormat)
{
	sName = "Sprites/" + sName + "." + sFormat;
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* rawSurface = IMG_Load(sName.c_str());
	if (rawSurface == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load surface", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		return nullptr;
	}
	optimizedSurface = SDL_ConvertSurface(rawSurface, m_ScreenSurface->format, 0);
	SDL_FreeSurface(rawSurface);
	if (optimizedSurface == nullptr)
	{
		std::cout << "SDL Error - Failed to optimize " << sName << "." << sFormat << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to optimize surface", ("Unable to optimize " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
	}

	return optimizedSurface;
}

void Window::BlitBackground(SDL_Surface* pSurf)
{
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = m_zWidth;
	stretchRect.h = m_zHeight;
	SDL_BlitScaled(pSurf, NULL, m_ScreenSurface, &stretchRect);
}
