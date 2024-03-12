#include "stdafx.h"
#include "Vector2.h"
namespace Common
{
	Vector2 _ptMouse = { 0.f, 0.f };

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2(int x, int y)
	{
		this->x = static_cast<int>(x);
		this->y = static_cast<int>(y);
	}

	Vector2 Vector2::operator+(const Vector2 & p)
	{
		Vector2 temp;
		temp.x = this->x + p.x;
		temp.y = this->y + p.y;
		return temp;
	}

	Vector2 Vector2::operator-(const Vector2 & p)
	{
		Vector2 temp;
		temp.x = this->x - p.x;
		temp.y = this->y - p.y;
		return temp;
	}

	Vector2 Vector2::operator+(const float & p)
	{
		Vector2 temp;
		temp.x = this->x + p;
		temp.y = this->y + p;
		return temp;
	}

	Vector2 Vector2::operator-(const float & p)
	{
		Vector2 temp;
		temp.x = this->x - p;
		temp.y = this->y - p;
		return temp;
	}

	Vector2 Vector2::operator*(const float & p)
	{
		Vector2 temp;
		temp.x = this->x * p;
		temp.y = this->y * p;
		return temp;
	}

	Vector2 Vector2::operator/(const float & p)
	{
		Vector2 temp;
		temp.x = this->x / p;
		temp.y = this->y / p;
		return temp;
	}

	const Vector2 & Vector2::operator+=(const Vector2 & p)
	{
		this->x += p.x;
		this->y += p.y;
		return (*this);
	}

	const Vector2 & Vector2::operator-=(const Vector2 & p)
	{
		this->x -= p.x;
		this->y -= p.y;
		return (*this);
	}

	const Vector2 & Vector2::operator+=(const float & p)
	{
		this->x += p;
		this->y += p;
		return (*this);
	}

	const Vector2 & Vector2::operator-=(const float & p)
	{
		this->x -= p;
		this->y -= p;
		return (*this);
	}

	const Vector2 & Vector2::operator*=(const float & p)
	{
		this->x *= p;
		this->y *= p;
		return (*this);
	}

	const Vector2 & Vector2::operator/=(const float & p)
	{
		this->x /= p;
		this->y /= p;
		return (*this);
	}

	bool Vector2::operator==(const Vector2 & p)
	{
		return this->x == p.x && this->y == p.y;
	}

	bool Vector2::operator!=(const Vector2 & p)
	{
		return this->x != p.x || this->y != p.y;
	}

	POINT Vector2::TypeTransPoint()
	{
		POINT point = {
			static_cast<LONG>(this->x),
			static_cast<LONG>(this->y)
		};
		return point;
	}
	D2D1_POINT_2F Vector2::TypeTransPoint2F()
	{
		D2D1_POINT_2F point2F = {
			x,
			y
		};
		return point2F;
	}
	Vector2 Vector2::TransInt()
	{
		return Vector2(static_cast<int>(x), static_cast<int>(y));
	}
}
