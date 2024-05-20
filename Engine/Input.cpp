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
	return m_aMouseButtonsState[nMouseButton];
}

bool Input::GetMouseButtonDown(uint8_t nMouseButton)
{
	return m_aMouseButtonsDown[nMouseButton];
}

bool Input::GetMouseButtonUp(uint8_t nMouseButton)
{
	return m_aMouseButtonsUp[nMouseButton];
}

float Input::GetMouseWheelDelta()
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
	return m_KeysState[static_cast<int>(nMouseButton)];
}

bool Input::GetKeyDown(E_Keys nMouseButton)
{
	return m_KeysDown[static_cast<int>(nMouseButton)];
}

bool Input::GetKeyUp(E_Keys nMouseButton)
{
	return m_KeysUp[static_cast<int>(nMouseButton)];
}

bool Input::GetShift()
{
	return m_KeysState[static_cast<int>(E_Keys::ShiftL)] || m_KeysState[static_cast<int>(E_Keys::ShiftR)];
}

bool Input::GetCtrl()
{
	return m_KeysState[static_cast<int>(E_Keys::CtrlL)] || m_KeysState[static_cast<int>(E_Keys::CtrlR)];
}

bool Input::GetAlt()
{
	return m_KeysState[static_cast<int>(E_Keys::AltL)] || m_KeysState[static_cast<int>(E_Keys::AltR)];
}

bool Input::WishQuit()
{
	return m_bWishQuit;
}
void Input::ForceQuit()
{
	m_bWishQuit = true;
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
	m_aMouseButtonsState[e.button.button-1] = true;
	m_aMouseButtonsDown[e.button.button-1] = true;
}

void Input::OnMouseButtonUp(const SDL_Event& e)
{
	m_aMouseButtonsState[e.button.button-1] = false;
	m_aMouseButtonsUp[e.button.button-1] = true;
}

void Input::OnMouseScroll(const SDL_Event& e)
{
	m_nScrollDelta = e.wheel.preciseY;
}
#pragma endregion