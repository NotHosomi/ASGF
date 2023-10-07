#include "Input.h"
#include <cassert>

Input* Input::m_pInstance = nullptr;

Input::Input()
{
}

void Input::Init()
{
	assert(m_pInstance == nullptr);
	m_pInstance = new Input();
}

Input* Input::Instance()
{
	return m_pInstance;
}

void Input::Close()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void Input::ProcessEvents()
{
	m_KeysDown.reset();
	m_KeysUp.reset();
	memset(m_aMouseButtonsDown.data(), false, m_aMouseButtonsDown.size());
	memset(m_aMouseButtonsUp.data(), false, m_aMouseButtonsUp.size());

	static SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN: OnKeyDown(e);
			break;
		case SDL_KEYUP: OnKeyUp(e);
			break;
		case SDL_MOUSEMOTION: OnMouseMove(e);
			break;
		case SDL_MOUSEBUTTONDOWN: OnMouseButtonDown(e);
			break;
		case SDL_MOUSEBUTTONUP: OnMouseButtonUp(e);
			break;
		case SDL_QUIT: m_bWishQuit = true;
			break;
		}
	}
}

/*
*  Getters
*/
#pragma region Getters
bool Input::GetMouseButton(uint8_t nMouseButton)
{
	return false;
}

bool Input::GetMouseButtonDown(uint8_t nMouseButton)
{
	return false;
}

bool Input::GetMouseButtonUp(uint8_t nMouseButton)
{
	return false;
}

int Input::GetMouseWheelDelta()
{
	return m_nScrollDelta;
}

SDL_Point Input::GetMousePos()
{
	return { m_nMouseX, m_nMouseY };
}

int Input::GetMouseX()
{
	return m_nMouseX;
}

int Input::GetMouseY()
{
	return m_nMouseY;
}

bool Input::GetKey(E_Keys nMouseButton)
{
	return false;
}

bool Input::GetKeyDown(E_Keys nMouseButton)
{
	return false;
}

bool Input::GetKeyUp(E_Keys nMouseButton)
{
	return false;
}

bool Input::GetShift()
{
	return false;
}

bool Input::GetCtrl()
{
	return false;
}

bool Input::GetAlt()
{
	return false;
}

bool Input::WishQuit()
{
	return m_bWishQuit;
}
#pragma endregion

/*
*  Handlers
*/
#pragma region Handlers
void Input::OnKeyDown(const SDL_Event& e)
{
	m_KeysState[e.key.keysym.scancode] = 1;
	m_KeysDown[e.key.keysym.scancode] = 1;
}

void Input::OnKeyUp(const SDL_Event& e)
{
	m_KeysState[e.key.keysym.scancode] = 0;
	m_KeysUp[e.key.keysym.scancode] = 1;
}

void Input::OnMouseMove(const SDL_Event& e)
{
	SDL_GetMouseState(&m_nMouseX, &m_nMouseY);
}

void Input::OnMouseButtonDown(const SDL_Event& e)
{
	m_aMouseButtonsState[e.button.button] = true;
	m_aMouseButtonsDown[e.button.button] = true;
}

void Input::OnMouseButtonUp(const SDL_Event& e)
{
	m_aMouseButtonsState[e.button.button] = false;
	m_aMouseButtonsUp[e.button.button] = true;
}

void Input::OnMouseScroll(const SDL_Event& e)
{
	m_nScrollDelta = e.wheel.preciseY;
}
#pragma endregion