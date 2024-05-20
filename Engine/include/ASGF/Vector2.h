#pragma once
#include <cmath>

template <typename T>
class Vector2
{
public:
	// construction
	Vector2(T x_, T y_) : x(x_), y(y_) {}
	Vector2() = default;
	~Vector2() = default;
	Vector2(const Vector2 & rhs) = default;
	Vector2(Vector2 && rhs) = default;
	Vector2& operator= (const Vector2 & rhs) = default;
	Vector2& operator= (Vector2 && rhs) = default;

	// operations
	Vector2 operator*(T scalar)
	{
		Vector2 vec(*this);
		vec.x *= scalar;
		vec.y *= scalar;
		return vec;
	}
	Vector2 operator+(const Vector2& operand)
	{
		Vector2 vec(*this);
		vec.x += operand.x;
		vec.y += operand.y;
		return vec;
	}
	Vector2 operator-(const Vector2& operand)
	{
		Vector2 vec(*this);
		vec.x -= operand.x;
		vec.y -= operand.y;
		return vec;
	}
	bool operator==(const Vector2& operand)
	{
		return (x == operand.x && y == operand.y);
	}
	void normalise()
	{
		float lcl_magnitude = magnitude();

		if (lcl_magnitude == 0)
		{
			return;
		}

		x /= lcl_magnitude;
		y /= lcl_magnitude;
	}
	float magnitude()
	{
		return sqrtf((x * x) + (y * y));
	}

	// data
	T x = 0;
	T y = 0;
};