#pragma once

#ifndef COMMON_ENUM_H
#define COMMON_ENUM_H

	enum Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};


	enum ObjectType
	{
		PLAYER,
		MONSTER,
		WALL,
		DOOR,
		OBJECT_TYPE_END
	};

	const int direction = 4;  // 0   1   2   3
	static int dx[direction] = { 1,  0, -1,  0 };
	static int dy[direction] = { 0,  1,  0, -1 };

	const int allDirection = 9;
	static int xdx[allDirection] = { 0, 1,  0, -1,  0, 1, -1,  1, -1 };
	static int xdy[allDirection] = { 0, 0,  1,  0, -1, 1, -1, -1,  1 };



#endif // !COMMON_ENUM_H
