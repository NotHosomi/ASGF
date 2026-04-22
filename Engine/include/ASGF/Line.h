#pragma once
#include "TypeTraits.h"
#include "Vector2.h"
#include "Circle.h"

template <NumericType T>
struct Line
{
	Line() = default;
	T x1 = 0;
	T x2 = 0;
	T y1 = 0;
	T y2 = 0;

	template<NumericType _Ty>
	Line<T>(Vector2<_Ty> start, Vector2<_Ty> end);

	template<NumericType _Ty>
	bool Intersects(const Line<_Ty>& other) const;

	template<NumericType _Ty>
	bool Intersects(const Circle<_Ty>& other) const;
};

template<NumericType T>
template<NumericType _Ty>
inline Line<T>::Line(Vector2<_Ty> start, Vector2<_Ty> end)
{
	x1 = start.x;
	x2 = end.x;
	y1 = start.y;
	y2 = end.y;
}

template<NumericType T>
template<NumericType _Ty>
inline bool Line<T>::Intersects(const Line<_Ty>& o) const
{
	float demoninator = (x1 - x2) * (o.y1 - o.y2) - (y1 - y2) * (o.x1 - o.x2);
	if (demoninator == 0) { return false; }

	float t = ((x1 - o.x1) * (o.y1 - o.y2) - (y1 - o.y1) * (o.x1 - o.x2)) / demoninator;
	float u = ((x1 - o.x1) * (y1 - y2) - (y1 - o.y1) * (x1 - x2)) / demoninator;

	return t > 0 && t < 1 && u > 0 && u < 1;
}

template<NumericType T>
template<NumericType _Ty>
inline bool Line<T>::Intersects(const Circle<_Ty>& o) const
{
	if ((x1 < o.x - o.r && x2 < o.x - o.r) ||
		(x1 > o.x + o.r && x2 > o.x + o.r) ||
		(y1 < o.y - o.r && y2 < o.y - o.r) ||
		(y1 > o.y + o.r && y2 > o.y + o.r))
	{
		return false;
	}

	float A = y1 - y1;
	float B = x1 - x2;
	float C = x2 * y1 - x1 * y2;
	float a = A*A + B*B;
	float b, c;
	if (abs(B) > 0)
	{
		b = 2 * (A * C + A * B * o.y - B*B * o.x);
		c = C*C + 2 * B * C * o.y - B*B * (o.r*o.r - o.x*o.x - o.y*o.y);
	}
	else
	{
		b = 2 * (B * C + A * B * o.x - A*A * o.y*o.y);
		c = C*C + 2 * A * C * o.x - A*A * (o.r*o.r - o.x*o.x - o.y*o.y);
	}
	return (b * b - 4 * a * c) >= 0;
}
