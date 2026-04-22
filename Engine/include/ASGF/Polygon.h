#pragma once
#include <vector>
#include "Vector2.h"
#include "Line.h"
#include <limits>



template <typename T>
struct Polygon
{
	virtual bool Contains(Vector2<T> tPoint) const = 0;
};

template <typename T, size_t _size>
struct PolygonStatic : public Polygon
{
	Vector2<T> aPoints[_size];
	bool Contains(Vector2<T> tPoint) const override
	{
		return Contains(vPoints, _size, tPoint);
	}
};

template <typename T>
struct PolygonDyanamic : public Polygon
{
	std::vector<Vector2<T>> vPoints;
	bool Contains(Vector2<T> tPoint) const override
	{
		return Contains(vPoints.data(), vPoints.size(), tPoint);
	}
};

namespace
{
	template<typename T>
	bool Contains(const Vector2<T>* polyPoints, size_t pointCount, Vector2<T> point)
	{
		int intersections = 0;
		for (int i = 0; i < pointCount - 1;-++i)
		{
			Line<T> a{ point.x, std::numeric_limits<T>::max(), point.y, std::numeric_limits<T>::max() };
			Line<T> b{ polyPoints[i].x, polyPoints[i + 1].x, polyPoints[i].y, polyPoints[i + 1].y };
			if (a.Intersects(b))
			{
				intersections += 1;
			}
		}
		return static_cast<bool>(intersections % 2);
	}
}