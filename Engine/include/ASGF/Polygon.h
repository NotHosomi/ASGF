#pragma once
#include "Vector2.h"

template <typename T, size_t _size>
struct Polygon
{
	T x[_size];
	T y[_size];


	//template <NumericType _Ty>
	//void Contains(Vector2<_Ty> tPoint) const;
};

//template<NumericType T>
//template<NumericType _Ty>
//inline bool Polygon<T>::Contains(Vector2<_Ty> point) const
//{
//	// todo
//}