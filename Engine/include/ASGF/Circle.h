#pragma once
#include "ConceptNumeric.h"
#include "Vector2.h"
#include "Rect.h"

template <NumericType T>
struct Circle
{
	T x;
	T y;
	T r;

	template <NumericType _Ty>
	bool Contains(Vector2<_Ty> point);

	template <NumericType _Ty>
	bool Overlaps(Circle<_Ty> other);

	template <NumericType _Ty>
	bool Overlaps(Rect<_Ty> other);
};

template<NumericType T>
template<NumericType _Ty>
inline bool Circle<T>::Contains(Vector2<_Ty> point)
{
	Vector2<T> delta = { point.x - x, point.y - y };
	return delta.magnitude2 <= r * r;
}

template<NumericType T>
template<NumericType _Ty>
inline bool Circle<T>::Overlaps(Circle<_Ty> other)
{
	Vector2<T> deltaC = { other.x - x, other.y - y };
	T deltaR = other.r + r;
	return delta.magnitude2() <= deltaR * deltaR;
}

template<NumericType T>
template<NumericType _Ty>
inline bool Circle<T>::Overlaps(Rect<_Ty> other)
{
	return
		(y >= other.y && y <= other.y + other.h && x + r >= other.x && x <= other.x + r) ||
		(x >= other.x && x <= other.x + other.w && y + r >= other.x && y <= other.y + r) ||
		Contains({other.x, other.y}) ||
		Contains({other.x + other.w, other.y}) ||
		Contains({other.x + other.w, other.y + other.h}) ||
		Contains({other.x, other.y + other.h});
}

