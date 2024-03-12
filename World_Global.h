#pragma once

#ifndef WORLD_GROBAL_H
#define WORLD_GROBAL_H
#include "stdafx.h"
namespace Common
{
	//=======================================
	// ���� ��� ����
	//=======================================

	// 1. ������ â
	/////////////////////////////////////////

	// ���� ������ ���� ũ��
	const float _WINSIZE_X = 1400;
	const float _WINSIZE_Y = 800;

	// ������ ���� ���� ��ǥ
	const float _WINSTART_X = 200;
	const float _WINSTART_Y = 100;

	// ������ �߾� ��ǥ
	const Vector2 _WINSIZE_CENTER = { _WINSIZE_X/2, _WINSIZE_Y/2 };

	// �� ũ��
	float _MAP_SIZE_X = 0;
	float _MAP_SIZE_Y = 0;

	/////////////////////////////////////////

	// 2. Ÿ���� ũ��
	/////////////////////////////////////////

	// ǥ�� Ÿ�� ũ��
	const float _TILESIZE_X = 60;
	const float _TILESIZE_Y = 60;
	// ǥ�� Ÿ�� ������ ũ��
	const float _TILESIZE_HALF_X = _TILESIZE_X / 2;
	const float _TILESIZE_HALF_Y = _TILESIZE_Y / 2;

	const Vector2 TILEIMAGESIZE = { _TILESIZE_X, _TILESIZE_Y };

	/////////////////////////////////////////

	//=======================================
	// ��ũ�� ���
	//=======================================

	// ������ ũ��
#define WINSIZE_X _WINSIZE_X
#define WINSIZE_Y _WINSIZE_Y

	// �� ũ��
#define MAP_SIZE_X _MAP_SIZE_X
#define MAP_SIZE_Y _MAP_SIZE_Y

	// ������ �߾� ��ǥ
#define WINSIZE_CENTER _WINSIZE_CENTER

	// Ÿ���� ũ��
#define TILESIZE_X _TILESIZE_X
#define TILESIZE_Y _TILESIZE_Y

	// Ÿ���� ���� ũ��
#define TILESIZE_HALF_X _TILESIZE_HALF_X
#define TILESIZE_HALF_Y _TILESIZE_HALF_Y

#define TILEIMAGESIZE TILEIMAGESIZE
}
#endif // !WORLD_GROBAL_H