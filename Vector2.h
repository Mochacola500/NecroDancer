#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H
namespace Common
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float x, float y);
		Vector2(int x, int y);

		POINT TypeTransPoint();
		D2D1_POINT_2F TypeTransPoint2F();

		Vector2 TransInt();

		//////////////////////////////////////////// 연산자 및 생성자 그리고 소멸자
		Vector2 operator+ (const Vector2& p);
		Vector2 operator- (const Vector2& p);

		Vector2 operator+ (const float& p);
		Vector2 operator- (const float& p);
		Vector2 operator* (const float& p);
		Vector2 operator/ (const float& p);

		const Vector2 & operator+= (const Vector2& p);
		const Vector2 & operator-= (const Vector2& p);

		const Vector2 & operator+= (const float& p);
		const Vector2 & operator-= (const float& p);
		const Vector2 & operator*= (const float& p);
		const Vector2 & operator/= (const float& p);

		bool operator == (const Vector2& p);
		bool operator != (const Vector2& p);

		Vector2() = default;
		~Vector2() = default;

	};

	extern Vector2 _ptMouse;
}
#endif // !VECTOR2_H

