#pragma once

#ifndef COMMON_FIGURE_H
#define COMMON_FIGURE_H
#include "FloatRect.h"
#include "Vector2.h"
namespace Common
{
	// 원 그리기 - 벡터
	inline D2D1_ELLIPSE EllipseMake(const Vector2 start, float radius)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = start.x;
		ellipse.point.y = start.y;
		ellipse.radiusX = radius;
		ellipse.radiusY = radius;
		return ellipse;
	}

	// 사각형 - 사각형 충돌
	inline bool IntersectRect(const FloatRect& lhs, const FloatRect& rhs)
	{
		return
			lhs.left < rhs.right && lhs.right > rhs.left &&
			lhs.top < rhs.bottom && lhs.bottom > rhs.top;
	}

	// 점 - 사각형 충돌
	inline bool PtInRect(const Vector2 point, const FloatRect& rhs)
	{
		return
			point.x > rhs.left && point.x < rhs.right &&
			point.y > rhs.top && point.y < rhs.bottom;
	}

	// Bottom 기준 정렬
	inline bool SortIsHighBottom(const FloatRect& lhs, const FloatRect& rhs)
	{
		return lhs.bottom > rhs.bottom;
	}

	// FloatRect 좌우 이동
	inline void RectMoveToWidth(FloatRect& lhs, float amount)
	{
		lhs.left += amount;
		lhs.right += amount;
	}

	// FloatRect 상하 이동
	inline void RectMoveToHeight(FloatRect& lhs, float amount)
	{
		lhs.top += amount;
		lhs.bottom += amount;
	}

	// FloatRect 대각 이동 left top -> right bottom 우선
	inline void RectMoveToDiagonal(FloatRect& lhs, float amount)
	{
		lhs.left += amount;
		lhs.top += amount;
		lhs.right += amount;
		lhs.bottom += amount;
	}

}
#endif // !COMMON_FIGURE_H