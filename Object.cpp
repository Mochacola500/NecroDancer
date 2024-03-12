#include "stdafx.h"
#include "Object.h"
#include "EventTime.h"

// 우방향을 기준으로 축 변경
Vector2 Object::DirectionAxis(Direction dir, int x, int y)
{
	int temp = 0;

	switch (dir)
	{
	case LEFT:
		x = -x;
		y = -y;
		return Vector2(mCenter.x + x * TILESIZE_X, mCenter.y + y * TILESIZE_Y);

	case RIGHT:
		// 우방향 기준 - 바로 리턴
		return Vector2(mCenter.x + x * TILESIZE_X, mCenter.y + y * TILESIZE_Y);
	case UP:
		temp = x;
		x = -y;
		y = -temp;
		return Vector2(mCenter.x + x * TILESIZE_X, mCenter.y + y * TILESIZE_Y);
	case DOWN:
		temp = x;
		x = y;
		y = temp;
		return Vector2(mCenter.x + x * TILESIZE_X, mCenter.y + y * TILESIZE_Y);
	}
}


float Object::GetAxis(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		return 180.f;
	case RIGHT:
		return 0.f;
	case UP:
		return 270.f;
	case DOWN:
		return 90.f;
	}
}

Vector2 Object::Rotation(Direction dir, Vector2 size)
{
	switch (dir)
	{
	case RIGHT:
	case LEFT:
	case UP:
	case DOWN:
		return Vector2(size.x, size.y);
	}
}


Vector2 Object::DirectionAxisImage(Direction dir, int x, int y)
{
	int temp = 0;

	switch (dir)
	{
	case LEFT:
		x = -x;
		y = -y;
		return Vector2(x, y);
	case RIGHT:
		// 우방향 기준 - 바로 리턴
		return Vector2(x, y);
	case UP:
		temp = x;
		x = -y;
		y = -temp;
		return Vector2(x, y);
	case DOWN:
		temp = x;
		x = y;
		y = temp;
		return Vector2(x, y);
	}
}

