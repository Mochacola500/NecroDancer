#include "stdafx.h"
#include "FloatRect.h"



namespace Common
{
	FloatRect::FloatRect(float left, float top, float right, float bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	FloatRect::FloatRect(const Vector2 & leftTop, const Vector2 & rightBottom)
	{
		this->left = leftTop.x;
		this->top = leftTop.y;
		this->right = rightBottom.x;
		this->bottom = rightBottom.y;
	}

	void FloatRect::RectMakeCenter(const Vector2 & center, float width, float height)
	{
		this->left = center.x - width / 2.f;
		this->right = center.x + width / 2.f;
		this->top = center.y - height / 2.f;
		this->bottom = center.y + height / 2.f;
	}

	RECT FloatRect::TypeTransRect()
	{
		RECT rc = {
			static_cast<LONG>(this->left),
			static_cast<LONG>(this->top),
			static_cast<LONG>(this->right),
			static_cast<LONG>(this->bottom)
		};
		return rc;
	}

	D2D1_RECT_F FloatRect::TypeTransRectF()
	{
		D2D1_RECT_F rc = {
			this->left,
			this->top,
			this->right,
			this->bottom
		};
		return rc;
	}

	FloatRect FloatRect::operator+(const FloatRect & p)
	{
		FloatRect temp;
		temp.left = this->left + p.left;
		temp.right = this->right + p.right;
		temp.top = this->top + p.top;
		temp.bottom = this->bottom + p.bottom;
		return temp;
	}

	FloatRect FloatRect::operator-(const FloatRect & p)
	{
		FloatRect temp;
		temp.left = this->left - p.left;
		temp.right = this->right - p.right;
		temp.top = this->top - p.top;
		temp.bottom = this->bottom - p.bottom;
		return temp;
	}

	FloatRect FloatRect::operator+(const Vector2 & p)
	{
		FloatRect temp;
		temp.left = this->left + p.x;
		temp.right = this->right + p.x;
		temp.top = this->top + p.y;
		temp.bottom = this->bottom + p.y;
		return temp;
	}

	FloatRect FloatRect::operator-(const Vector2 & p)
	{
		FloatRect temp;
		temp.left = this->left - p.x;
		temp.right = this->right - p.x;
		temp.top = this->top - p.y;
		temp.bottom = this->bottom - p.y;
		return temp;
	}

	FloatRect FloatRect::operator+(const float & p)
	{
		FloatRect temp;
		temp.left = this->left + p;
		temp.right = this->right + p;
		temp.top = this->top + p;
		temp.bottom = this->bottom + p;
		return temp;
	}

	FloatRect FloatRect::operator-(const float & p)
	{
		FloatRect temp;
		temp.left = this->left - p;
		temp.right = this->right - p;
		temp.top = this->top - p;
		temp.bottom = this->bottom - p;
		return temp;
	}

	FloatRect FloatRect::operator*(const float & p)
	{
		FloatRect temp;
		temp.left = this->left * p;
		temp.right = this->right * p;
		temp.top = this->top * p;
		temp.bottom = this->bottom * p;
		return temp;
	}

	FloatRect FloatRect::operator/(const float & p)
	{
		FloatRect temp;
		temp.left = this->left / p;
		temp.right = this->right / p;
		temp.top = this->top / p;
		temp.bottom = this->bottom / p;
		return temp;
	}

	const FloatRect & FloatRect::operator+=(const FloatRect & p)
	{
		this->left += p.left;
		this->right += p.right;
		this->top += p.top;
		this->bottom += p.bottom;
		return (*this);
	}

	const FloatRect & FloatRect::operator+=(const Vector2 & p)
	{
		this->left += p.x;
		this->right += p.x;
		this->top += p.y;
		this->bottom += p.y;
		return (*this);
	}

	const FloatRect & FloatRect::operator-=(const FloatRect & p)
	{
		this->left -= p.left;
		this->right -= p.right;
		this->top -= p.top;
		this->bottom -= p.bottom;
		return (*this);
	}

	const FloatRect & FloatRect::operator-=(const Vector2 & p)
	{
		this->left -= p.x;
		this->right -= p.x;
		this->top -= p.y;
		this->bottom -= p.y;
		return (*this);
	}

	const FloatRect & FloatRect::operator+=(const float & p)
	{
		this->left += p;
		this->right += p;
		this->top += p;
		this->bottom += p;
		return (*this);
	}

	const FloatRect & FloatRect::operator-=(const float & p)
	{
		this->left -= p;
		this->right -= p;
		this->top -= p;
		this->bottom -= p;
		return (*this);
	}

	const FloatRect & FloatRect::operator*=(const float & p)
	{
		this->left *= p;
		this->right *= p;
		this->top *= p;
		this->bottom *= p;
		return (*this);
	}

	const FloatRect & FloatRect::operator/=(const float & p)
	{
		this->left /= p;
		this->right /= p;
		this->top /= p;
		this->bottom /= p;
		return (*this);
	}

	bool FloatRect::operator==(const FloatRect & p)
	{
		return this->left == p.left && this->right == p.right &&
			this->top == p.top && this->bottom == p.bottom;
	}

	bool FloatRect::operator!=(const FloatRect & p)
	{
		return this->left != p.left || this->right != p.right ||
			this->top != p.top || this->bottom != p.bottom;
	}
}