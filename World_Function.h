#pragma once

#ifndef WORLD_FUNCTION_H
#define WORLD_FUNCTION_H
#include "stdafx.h"
namespace Common
{
	//=======================================
	// 타일의 인덱스
	//=======================================

	//* 벡터2를 타일의 인덱스 X로 반환 합니다.
	inline float TileIndexX(const Vector2 lhs)
	{
		return (lhs.x - lhs.y) * TILESIZE_X;
	}

	//* 벡터2를 타일의 인덱스 Y로 반환 합니다.
	inline float TileIndexY(const Vector2 lhs)
	{
		return (lhs.x + lhs.y) * TILESIZE_Y;
	}

	//* 벡터2를 타일의 X,Y 인덱스로 반환 합니다.
	inline Vector2 Vector2ToTileIndex(const Vector2 lhs)
	{
		return Vector2(TileIndexX(lhs), TileIndexY(lhs));
	}

	// 대상이 화면 안에 있는가?
	inline bool IsInWindow(const FloatRect& rc)
	{
		if (IntersectRect(rc,FloatRect(0,0,WINSIZE_X,WINSIZE_Y)))
		{
			return false;
		}
		return true;
	}

	// 대상이 화면 안에 있는가?
	inline bool IsInWindow(const Vector2& lhs)
	{
		if ((lhs.x > WINSIZE_X || lhs.x < 0) &&
			(lhs.y > WINSIZE_Y || lhs.y < 0))
		{
			return false;
		}
		return true;
	}

	inline float GetDistance(Vector2 start, Vector2 end)
	{
		float dx = start.x - end.x;
		float dy = start.y - end.y;
		return sqrt(dx * dx + dy * dy);
	}

	inline float SetAngle(Vector2 pt1, Vector2 pt2)
	{
		int  nWidth, nHeight;
		float fHypotenuse;
		float fAngle;
		//pt1이 중심점이다
		nWidth = pt2.x - pt1.x;
		nHeight = pt2.y - pt1.y;
		fHypotenuse = float(sqrt(nWidth * nWidth + nHeight * nHeight));

		fAngle = acosf(nWidth / fHypotenuse);

		if (pt2.y > pt1.y)
		{
			fAngle = 2 * 3.141592f - fAngle;
			if (fAngle >= 2 * 3.141592f) fAngle -= 2 * 3.141592f;
		}

		return fAngle;
	}

	inline Direction CalculateDirection(Vector2 lhs, Vector2 rhs)
	{
		int dx = static_cast<int>((lhs.x - rhs.x) / TILESIZE_X);
		int dy = static_cast<int>((lhs.y - rhs.y) / TILESIZE_Y);

		if (dx == 1 && dy == 0)
		{
			return LEFT;
		}
		else if (dx == -1 && dy == 0)
		{
			return RIGHT;
		}
		else if (dx == 0 && dy == 1)
		{
			return UP;
		}
		else if (dx == 0 && dy == -1)
		{
			return DOWN;
		}
	}
}
#endif // !WORLD_FUNCTION_H