#include "stdafx.h"
#include "D2DRenderer.h"

/**********************************************************************************************
# �ؽ�Ʈ
@ writePosition : ���� ��ǥ
@ layout        : ����� ���̾�
@ color         : ��
@ alpha         : ���� - �⺻(1.0f)
************************************************************************************************/
void D2DRenderer::RenderText(Vector2 writePosition, IDWriteTextLayout* layout, ColorF::Enum color, float alpha)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawTextLayout(writePosition.TypeTransPoint2F(), layout, mCommonBrush);
}
/**********************************************************************************************
# ��
@ start       : ���� ��ǥ
@ end         : �� ��ǥ
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
@ strokeWidth : ���� �β�
************************************************************************************************/
void D2DRenderer::DrawLine( Vector2 start,  Vector2  end, 
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawLine(start.TypeTransPoint2F(), end.TypeTransPoint2F(), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# �簢��
@ rc          : �簢�� ��ġ
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
@ strokeWidth : ���� �β�
************************************************************************************************/
void D2DRenderer::DrawRectangle(FloatRect  rc,
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawRectangle(rc.TypeTransRectF(), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# ������
@ rc          : �簢�� ��ġ
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
@ strokeWidth : ���� �β�
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
# ��
@ origin      : ���� ��ǥ
@ radius      : �������� ũ��
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
@ strokeWidth : ���� �β�
************************************************************************************************/
void D2DRenderer::DrawEllipse( Vector2 origin,  float  radius,
	D2D1::ColorF::Enum  color, float alpha, float  strokeWidth)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->DrawEllipse(&EllipseMake(origin, radius), mCommonBrush, strokeWidth);
}
/**********************************************************************************************
# �簢�� - fill
@ rc          : �簢�� ��ġ
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
************************************************************************************************/
void D2DRenderer::FillRectangle(FloatRect  rc, D2D1::ColorF::Enum  color, float alpha)
{
	//D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(rc.right - rc.left, rc.bottom - rc.top);
	//D2DRENDER->GetRenderTarget()->SetTransform(scale);

	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->FillRectangle(rc.TypeTransRectF(), mCommonBrush);
}
/**********************************************************************************************
# �� - fill
@ origin      : ���� ��ǥ
@ radius      : �������� ũ��
@ ColorF      : ��
@ alpha       : ���� - �⺻(1.0f)
************************************************************************************************/
void D2DRenderer::FiilEllipse( Vector2  origin,  float  radius,  D2D1::ColorF::Enum  color, float  alpha)
{
	mCommonBrush->SetColor(D2D1::ColorF(color, alpha));
	mD2DRender->FillEllipse(&EllipseMake(origin, radius), mCommonBrush);
}