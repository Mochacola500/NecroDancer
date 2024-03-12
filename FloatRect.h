#pragma once
#ifndef FLOAT_RECT_H
#define FLOAT_RECT_H

namespace Common
{
	struct FloatRect
	{
		float left;
		float top;
		float right;
		float bottom;

		FloatRect(float left, float top, float right, float bottom);
		FloatRect(const Vector2& leftTop, const Vector2& rightBottom);
		void RectMakeCenter(const Vector2& center, float width, float height);
		RECT TypeTransRect();
		D2D1_RECT_F TypeTransRectF();

		//////////////////////////////////////////// 연산자 및 생성자 그리고 소멸자
		FloatRect operator+ (const FloatRect& p);
		FloatRect operator- (const FloatRect& p);
		FloatRect operator+ (const Vector2& p);
		FloatRect operator- (const Vector2& p);

		FloatRect operator+ (const float& p);
		FloatRect operator- (const float& p);
		FloatRect operator* (const float& p);
		FloatRect operator/ (const float& p);

		const FloatRect & operator+= (const FloatRect& p);
		const FloatRect & operator-= (const FloatRect& p);
		const FloatRect & operator+= (const Vector2& p);
		const FloatRect & operator-= (const Vector2& p);

		const FloatRect & operator+= (const float& p);
		const FloatRect & operator-= (const float& p);
		const FloatRect & operator*= (const float& p);
		const FloatRect & operator/= (const float& p);

		bool operator == (const FloatRect & p);
		bool operator != (const FloatRect & p);

		FloatRect() = default;
		~FloatRect() = default;

	};
}
#endif // !FLOAT_RECT_H
