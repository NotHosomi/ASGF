#pragma once
#include <cmath>
#include "TypeTraits.h"

template <NumericType T> 
struct Vector2
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
	Vector2 operator*(T scalar) const
	{
		Vector2 vec(*this);
		vec.x *= scalar;
		vec.y *= scalar;
		return vec;
	}
	Vector2 operator/(T scalar) const
	{
		Vector2 vec(*this);
		vec.x /= scalar;
		vec.y /= scalar;
		return vec;
	}
	Vector2 operator+(const Vector2& operand) const
	{
		Vector2 vec(*this);
		vec.x += operand.x;
		vec.y += operand.y;
		return vec;
	}
	Vector2 operator-(const Vector2& operand) const
	{
		Vector2 vec(*this);
		vec.x -= operand.x;
		vec.y -= operand.y;
		return vec;
	}
	Vector2<T>& operator+=(const Vector2& operand)
	{
		x += operand.x;
		y += operand.y;
		return *this;
	}
	Vector2<T>& operator-=(const Vector2& operand)
	{
		x -= operand.x;
		y -= operand.y;
		return *this;
	}
	bool operator==(const Vector2& operand) const
	{
		return (x == operand.x && y == operand.y);
	}
	bool operator!=(const Vector2& operand) const
	{
		return (x != operand.x || y != operand.y);
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
	Vector2<T> normalised()
	{
		float lcl_magnitude = magnitude();

		if (lcl_magnitude == 0)
		{
			return { 0,0 };
		}

		return { x / lcl_magnitude, y / lcl_magnitude };
	}
	float magnitude() const
	{
		return sqrtf(static_cast<float>((x * x) + (y * y)));
	}
	T magnitude2() const
	{
		return (x * x) + (y * y);
	}
	template <typename T>
	Vector2<T> cast() const
	{
		return Vector2<T>{static_cast<T>(x), static_cast<T>(y)};
	}
	// rotate an amount of radians
	Vector2<T>& Rotate(float theta)
	{
		float c = cos(theta);
		float s = sin(theta);

		Vector2<float> temp;
		temp.x = x * c - y * s;
		temp.y = x * s + y * c;
		x = temp.x;
		y = temp.y;
		return *this;
	}
	Vector2<T> Rotation(float theta)
	{
		float c = cos(theta);
		float s = sin(theta);

		Vector2<float> out;
		out.x = x * c - y * s;
		out.y = x * s + y * c;
		return out;
	}
	float Angle(const Vector2<T> other)
	{
		return atan2(other.y, other.x) - atan2(y, x);
	}
	float Dot(const Vector2<T> other)
	{
		return x * other.x + y * other.y;
	}

	// data
	T x = 0;
	T y = 0;
};
