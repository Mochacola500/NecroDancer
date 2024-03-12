#pragma once

#ifndef WORLD_GROBAL_H
#define WORLD_GROBAL_H
#include "stdafx.h"
namespace Common
{
	//=======================================
	// 전역 상수 정의
	//=======================================

	// 1. 윈도우 창
	/////////////////////////////////////////

	// 실제 윈도우 영역 크기
	const float _WINSIZE_X = 1400;
	const float _WINSIZE_Y = 800;

	// 윈도우 영역 시작 좌표
	const float _WINSTART_X = 200;
	const float _WINSTART_Y = 100;

	// 윈도우 중앙 좌표
	const Vector2 _WINSIZE_CENTER = { _WINSIZE_X/2, _WINSIZE_Y/2 };

	// 맵 크기
	float _MAP_SIZE_X = 0;
	float _MAP_SIZE_Y = 0;

	/////////////////////////////////////////

	// 2. 타일의 크기
	/////////////////////////////////////////

	// 표준 타일 크기
	const float _TILESIZE_X = 60;
	const float _TILESIZE_Y = 60;
	// 표준 타일 절반의 크기
	const float _TILESIZE_HALF_X = _TILESIZE_X / 2;
	const float _TILESIZE_HALF_Y = _TILESIZE_Y / 2;

	const Vector2 TILEIMAGESIZE = { _TILESIZE_X, _TILESIZE_Y };

	/////////////////////////////////////////

	//=======================================
	// 매크로 상수
	//=======================================

	// 윈도우 크기
#define WINSIZE_X _WINSIZE_X
#define WINSIZE_Y _WINSIZE_Y

	// 맵 크기
#define MAP_SIZE_X _MAP_SIZE_X
#define MAP_SIZE_Y _MAP_SIZE_Y

	// 윈도우 중앙 좌표
#define WINSIZE_CENTER _WINSIZE_CENTER

	// 타일의 크기
#define TILESIZE_X _TILESIZE_X
#define TILESIZE_Y _TILESIZE_Y

	// 타일의 절반 크기
#define TILESIZE_HALF_X _TILESIZE_HALF_X
#define TILESIZE_HALF_Y _TILESIZE_HALF_Y

#define TILEIMAGESIZE TILEIMAGESIZE
}
#endif // !WORLD_GROBAL_H