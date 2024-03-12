#pragma once

#ifndef COMMON_MATH_H
#define COMMON_MATH_H
#include "Vector2.h"
namespace Common
{
	// 정규화 
	inline void Nomarize(Vector2& lhs, float pixel = 1)
	{
		lhs.x < 0 ? lhs.x = -pixel : lhs.x = pixel;
		lhs.y < 0 ? lhs.y = -pixel : lhs.y = pixel;
	}

	// 내적
	inline float InnerProduct(Vector2 lhs, Vector2 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
}
#endif // !COMMON_MATH_H