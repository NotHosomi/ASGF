#pragma once
#include <SDL.h>
#include <bitset>
#include <unordered_map>
#include <functional>
#include <array>

constexpr int NUM_MOUSE_BUTTONS = 5;

enum class E_ButtonState
{
	press,		// 0b00
	release,	// 0b01
	held,		// 0b10
	up,			// 0b11
};

enum class E_Keys // aligned with SDL_SCANCODE
{
	A = SDL_SCANCODE_A ,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,Num0,
	Return, Escape, Backspace, Tab, Space, Minus, Equals, LeftBracket, RightBracket, Backslash,
	Semicolon = SDL_SCANCODE_SEMICOLON,Apostrophe,Grave,Comma,Period,Slash,Capslock,
	F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
	PrintScreen,ScrollLock,Pause,Insert,
	Home,PageUp,Delete,End,PageDown,Right,Left,Down,Up,NumLock,
	KeypadDivide, KeypadMultiply, KeypadMinus,KeypadPlus,
	Keypad1,Keypad2,Keypad3,Keypad4,Keypad5,Keypad6,Keypad7,Keypad8,Keypad9,Keypad0,
	KeypadEnter, KeypadEquals=SDL_SCANCODE_EQUALS,
	F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24,
	CtrlL=SDL_SCANCODE_LCTRL,ShiftL,AltL,WinL,CtrlR,ShiftR,AltR,WinR,
	KeyboardSize
};

class Input
{
// Singleton Pattern
private:
	Input();
	Input(Input const&) = delete;
	void operator=(Input const&) = delete;
	static Input* m_pInstance;
public:
	static void Init();
	static Input* Instance();
	static void Close();

// Interface
public:
	void ProcessEvents();

	// returns the current pixel coordinates of the cursor, relative to the window origin
	SDL_Point GetMousePos();
	int GetMouseX();
	int GetMouseY();

	// returns true if the button is currently down
	bool GetMouseButton(uint8_t nMouseButton);
	// returns true if the button was clicked this frame
	bool GetMouseButtonDown(uint8_t nMouseButton);
	// returns true if the button was released this frame
	bool GetMouseButtonUp(uint8_t nMouseButton);

	float GetMouseWheelDelta();

	// returns true is the key is currently down
	bool GetKey(E_Keys nMouseButton);
	// returns true if the key became pressed this frame
	bool GetKeyDown(E_Keys nMouseButton);
	// returns true if the key became unpressed this frame
	bool GetKeyUp(E_Keys nMouseButton);
	// Returns true if either shift key is currently down
	bool GetShift();
	// Returns true if either ctrl key is currently down
	bool GetCtrl();
	// Returns true if either alt key is currently down
	bool GetAlt();

	// Returns true if the user has requested to quit
	bool WishQuit();
	// Sets the quit flag to true
	void ForceQuit();

private:

	int m_nMouseX;
	int m_nMouseY;

	void OnKeyDown(const SDL_Event& e);
	void OnKeyUp(const SDL_Event& e);
	void OnMouseMove(const SDL_Event& e);
	void OnMouseButtonDown(const SDL_Event& e);
	void OnMouseButtonUp(const SDL_Event& e);
	void OnMouseScroll(const SDL_Event& e);

	std::bitset<static_cast<size_t>(E_Keys::KeyboardSize)> m_KeysState;
	std::bitset<static_cast<size_t>(E_Keys::KeyboardSize)> m_KeysDown;
	std::bitset<static_cast<size_t>(E_Keys::KeyboardSize)> m_KeysUp;
	std::array<bool, 5> m_aMouseButtonsState;
	std::array<bool, 5> m_aMouseButtonsDown;
	std::array<bool, 5> m_aMouseButtonsUp;
	float m_nScrollDelta = 0;
	bool m_bWishQuit = false;
};

// https://github.com/alexdantas/sdl2-platformer/blob/master/src/InputManager.hpp
