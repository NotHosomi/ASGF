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
	// preliminary bounding box check
	if ((x1 < o.x - o.r && x2 < o.x - o.r) ||
		(x1 > o.x + o.r && x2 > o.x + o.r) ||
		(y1 < o.y - o.r && y2 < o.y - o.r) ||
		(y1 > o.y + o.r && y2 > o.y + o.r))
	{
		return false;
	}

	const double dx = x2 - x1, dy = y2 - y1;
	const double fx = o.x - x1, fy = o.y - y1;
	const double len2 = dx * dx + dy * dy;

	// Degenerate segment -> point test
	const double t = len2 > 0 ? std::clamp((fx * dx + fy * dy) / len2, 0.0, 1.0) : 0.0;

	const double cx = fx - t * dx, cy = fy - t * dy;
	return cx * cx + cy * cy <= double(o.r) * o.r;
}
