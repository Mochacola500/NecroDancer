#include "stdafx.h"
#include "D2DRenderer.h"

/**********************************************************************************************
# 텍스트
@ writePosition : 시작 좌표
@ layout        : 출력할 레이어
@ color         : 색
@ alpha         : 투명도 - 기본(1.0f)
************************************************************************************************/
void D2DRenderer::RenderText(Vector2 writePosition, IDWriteTextLayout* layout, ColorF::Enum color, float alpha)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawTextLayout(writePosition.TypeTransPoint2F(), layout, mCommonBrush);
}
/**********************************************************************************************
# 선
@ start       : 시작 좌표
@ end         : 끝 좌표
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
@ strokeWidth : 선의 두께
************************************************************************************************/
void D2DRenderer::DrawLine( Vector2 start,  Vector2  end, 
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawLine(start.TypeTransPoint2F(), end.TypeTransPoint2F(), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# 사각형
@ rc          : 사각형 위치
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
@ strokeWidth : 선의 두께
************************************************************************************************/
void D2DRenderer::DrawRectangle(FloatRect  rc,
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawRectangle(rc.TypeTransRectF(), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# 마름모
@ rc          : 사각형 위치
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
@ strokeWidth : 선의 두께
************************************************************************************************/
void D2DRenderer::DrawRhombus(Vector2 center, D2D1::ColorF::Enum color, float alpha, float strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	Vector2 left = CAMERA->CorrecteLocation(&Vector2(center.x, center.y + TILESIZE_HALF_Y));
	Vector2 right = CAMERA->CorrecteLocation(&Vector2(center.x + TILESIZE_X, center.y + TILESIZE_HALF_Y));
	Vector2 top = CAMERA->CorrecteLocation(&Vector2(center.x + TILESIZE_HALF_X, center.y));
	Vector2 bottom = CAMERA->CorrecteLocation(&Vector2(center.x + TILESIZE_HALF_X, center.y + TILESIZE_Y));

	mD2DRender->DrawLine(left.TypeTransPoint2F(), top.TypeTransPoint2F(), mCommonBrush, strokeWidth);
	mD2DRender->DrawLine(top.TypeTransPoint2F(), right.TypeTransPoint2F(), mCommonBrush, strokeWidth);
	mD2DRender->DrawLine(right.TypeTransPoint2F(), bottom.TypeTransPoint2F(), mCommonBrush, strokeWidth);
	mD2DRender->DrawLine(bottom.TypeTransPoint2F(), left.TypeTransPoint2F(), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# 원
@ origin      : 시작 좌표
@ radius      : 반지름의 크기
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
@ strokeWidth : 선의 두께
************************************************************************************************/
void D2DRenderer::DrawEllipse( Vector2 origin,  float  radius,
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawEllipse(&EllipseMake(origin, radius), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# 사각형 - fill
@ rc          : 사각형 위치
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
************************************************************************************************/
void D2DRenderer::FillRectangle(FloatRect  rc, D2D1::ColorF::Enum  color, float alpha)
{
	//D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(rc.right - rc.left, rc.bottom - rc.top);
	//D2DRENDER->GetRenderTarget()->SetTransform(scale);

	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->FillRectangle(rc.TypeTransRectF(), mCommonBrush);
}
/**********************************************************************************************
# 원 - fill
@ origin      : 시작 좌표
@ radius      : 반지름의 크기
@ ColorF      : 색
@ alpha       : 투명도 - 기본(1.0f)
************************************************************************************************/
void D2DRenderer::FiilEllipse( Vector2  origin,  float  radius,  D2D1::ColorF::Enum  color, float  alpha)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->FillEllipse(&EllipseMake(origin, radius), mCommonBrush);
}