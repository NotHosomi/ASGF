#pragma once
#include "Vector2.h"
#include "TypeTraits.h"

template <NumericType T>
struct Rect
{
	T x;
	T y;
	T w;
	T h;

	template <NumericType _Ty>
	bool Overlaps(const Rect<_Ty>& other) const;

	template <NumericType _Ty>
	bool Contains(Vector2<_Ty> point) const;

	Vector2<T> Corner(int index) const;
};

template<NumericType T>
template<NumericType _Ty>
inline bool Rect<T>::Overlaps(const Rect<_Ty>& other) const
{
	return 
		other.x <= x+w &&
		other.y <= y+h &&
		other.x+other.w >= x &&
		other.y+other.h >= y;
}

template<NumericType T>
template<NumericType _Ty>
inline bool Rect<T>::Contains(Vector2<_Ty> point) const
{
	return
		point.x >= x &&
		point.y >= y &&
		point.x <= x + w &&
		point.y <= y + h;
}

template<NumericType T>
inline Vector2<T> Rect<T>::Corner(int index) const
{
	switch (index)
	{
	case 0: return { x, y };
	case 1: return { x + w, y };
	case 2: return { x + w, y + h };
	case 3: return { x, y + h };
	}
}
