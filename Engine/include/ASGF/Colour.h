#pragma once
#include <stdint.h>
struct Colour
{
	uint8_t r = 0xFF;
	uint8_t g = 0xFF;
	uint8_t b = 0xFF;
};

namespace Colours
{
	inline constexpr Colour White		{ 0xFF, 0xFF, 0xFF };
	inline constexpr Colour Black		{ 0x00, 0x00, 0x00 };

	inline constexpr Colour Red			{ 0xFF, 0x00, 0x00 };
	inline constexpr Colour Green		{ 0x00, 0xFF, 0x00 };
	inline constexpr Colour Blue		{ 0x00, 0x00, 0xFF };

	inline constexpr Colour DarkRed		{ 0x80, 0x00, 0x00 };
	inline constexpr Colour DarkGreen	{ 0x00, 0x80, 0x00 };
	inline constexpr Colour DarkBlue	{ 0x00, 0x00, 0x80 };

	inline constexpr Colour Cyan		{ 0x00, 0xFF, 0xFF };
	inline constexpr Colour Yellow		{ 0xFF, 0xFF, 0x00 };
	inline constexpr Colour Magenta		{ 0xFF, 0x00, 0xFF };

	inline constexpr Colour DarkCyan	{ 0x00, 0x80, 0x80 };
	inline constexpr Colour DarkYellow	{ 0x80, 0x80, 0x00 };
	inline constexpr Colour DarkMagenta	{ 0x80, 0x00, 0x80 };

	inline constexpr Colour Purple		{ 0x80, 0x00, 0x80 };
	inline constexpr Colour Brown		{ 0x8B, 0x45, 0x13 };
}