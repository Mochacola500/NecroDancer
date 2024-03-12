#include "stdafx.h"
#include "Image.h"

/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)

�������̹����� �ƴ� �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image(ID2D1Bitmap * const bitmap, const TagLoadedImageInfo & loadinfo, float alpha, float angle)
	: mBitmap(bitmap), mLoadInfo(loadinfo), mScale(1.f), mMaxFrameX(1), mMaxFrameY(1)
{
	this->mSize.x = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.y = (float)this->mBitmap->GetPixelSize().height;

	mAlpha = alpha;
	mAngle = angle;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.x;
	rc.height = mSize.y;
	this->mFrameInfo.push_back(rc);

}
/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)
@@ int maxFrameX : ���� ������ ��
@@ int maxFrameY : ���� ������ ��

������ �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image(ID2D1Bitmap * bitmap, const TagLoadedImageInfo & loadinfo, const int & maxFrameX, const int & maxFrameY, float alpha, float angle)
	: mBitmap(bitmap), mLoadInfo(loadinfo), mMaxFrameX(maxFrameX), mMaxFrameY(maxFrameY), mScale(1.f)
{
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.x / this->mMaxFrameX;
	float frameY = mSize.y / this->mMaxFrameY;

	mAlpha = alpha;
	mAngle = angle;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = i * (frameX);
			rc.y = j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->mFrameInfo.push_back(rc);
		}
	}
}
/********************************************************************************
## ~Image ##
��Ʈ�� ����
*********************************************************************************/
Image::~Image()
{
	SAFE_RELEASE(mBitmap);
}
/********************************************************************************
## Render ##
@@ int x : �׸� ��ǥ
@@ int y : �׸� ��ǥ
@@ Pivot::Enum pivot : �׸� �Ǻ�
*********************************************************************************/
void Image::Render( int x,  int y, const bool& isRelative)
{
	Vector2 renderPos((float)x, (float)y);
	//�׸� ������ = ������ * ������
	this->mSize.x = mSize.x * mScale;
	this->mSize.y = mSize.y * mScale;

	//ũ�� ������ ������� scale��� ���� 
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(mScale, mScale);
	Vector2 offset(0, 0);

	if (isRelative)
	{
		renderPos = CAMERA->CorrecteLocation(&renderPos);
	}			   

	//angle������ �������� ȸ�� ��� ���� 
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(mAngle, Vector2(renderPos/2).TypeTransPoint2F());
	//������ ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(renderPos.x, renderPos.y, renderPos.x + mSize.x, renderPos.y + mSize.y);
	//�̹����� ȭ�鿡 �׷��� ���� ����� ũ����� * ȸ����� * �̵���� 
	//����� ��ȯ��Ģ�� ������ �ȵǹǷ� �ݵ�� ���� ������ ���缭 ������ �־�� �Ѵ�. 
	D2DRENDER->GetRenderTarget()->SetTransform(scale * rotation);
	//������ ��û
	D2DRENDER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	//�������� �����ٸ� �ɼǰ� �⺻���� ����
	this->ResetRenderOption();
}

void Image::Render(Vector2 pos, const bool & isRelative)
{
	//�׸� ������ = ������ * ������
	this->mSize.x = mSize.x * mScale;
	this->mSize.y = mSize.y * mScale;

	//ũ�� ������ ������� scale��� ���� 
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(mScale, mScale);

	Vector2 temp = pos;
	if (isRelative)
	{
		temp = CAMERA->CorrecteLocation(&temp);
	}

	// �̹����� ȭ�� ���̸� �׸����� �ʴ´�.
	if (temp.x > WINSIZE_X || temp.y > WINSIZE_Y || temp.x + mSize.x < 0 || temp.y + mSize.y < 0)
	{
		ResetRenderOption();
		return;
	}

	//angle������ �������� ȸ�� ��� ���� 
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(mAngle, Vector2(temp / 2).TypeTransPoint2F());
	//������ ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(temp.x, temp.y, temp.x + mSize.x,temp.y + mSize.y);

	//�̹����� ȭ�鿡 �׷��� ���� ����� ũ����� * ȸ����� * �̵���� 
	//����� ��ȯ��Ģ�� ������ �ȵǹǷ� �ݵ�� ���� ������ ���缭 ������ �־�� �Ѵ�. 
	D2DRENDER->GetRenderTarget()->SetTransform(scale * rotation);
	//������ ��û
	D2DRENDER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	//�������� �����ٸ� �ɼǰ� �⺻���� ����
	this->ResetRenderOption();
}

void Image::Render(Vector2 pos, Vector2 index, const bool & isRelative)
{
	//�������� �ִ� �������� ����ٸ� �׸��� �ʴ´�. 
	if (index.x >= this->mMaxFrameX || index.y >= this->mMaxFrameY)
	{
		ResetRenderOption();
		return;
	}
	//���� �������ε��� 
	int frame = static_cast<int>(index.y * mMaxFrameX + index.x);

	//ũ�� ��� ���� 
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(mScale, mScale);

	if (isRelative)
	{
		pos = CAMERA->CorrecteLocation(&pos);
	}

	// �̹����� ȭ�� ���̸� �׸����� �ʴ´�.
	if (pos.x > WINSIZE_X || pos.y > WINSIZE_Y || pos.x + mSize.x < 0 || pos.y + mSize.y < 0)
	{
		ResetRenderOption();
		return;
	}

	//angle������ �������� ȸ�� ��� ���� 
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(mAngle, Vector2(pos / 2).TypeTransPoint2F());

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF(mFrameInfo[frame].x, mFrameInfo[frame].y,
		(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(mFrameInfo[frame].y + mFrameInfo[frame].height));

	//������� ����
	D2DRENDER->GetRenderTarget()->SetTransform(scale * rotation);

	//������ ��û
	D2DRENDER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);

	this->ResetRenderOption();
}
/********************************************************************************
## FrameRender ##
@@ int x : �׸� ��ǥ
@@ int y : �׸� ��ǥ
@@ int frameX : ���� ������
@@ int frameY : ���� ������
@@ Pivot::Enum pivot : �׸� �Ǻ�
*********************************************************************************/
void Image::FrameRender( Vector2 pos,  Vector2 frameXY, const bool& isRelative, float alpha)
{
	//�������� �ִ� �������� ����ٸ� �׸��� �ʴ´�. 
	if (frameXY.x >= this->mMaxFrameX || frameXY.y >= this->mMaxFrameY)
	{
		ResetRenderOption();
		return;
	}
	//���� �������ε��� 
	int frame = static_cast<int>(frameXY.y * mMaxFrameX + frameXY.x);


	if (isRelative)
	{
		pos = CAMERA->CorrecteLocation(&pos);
	}
	
	// �̹����� ȭ�� ���̸� �׸����� �ʴ´�.
	if (pos.x > WINSIZE_X || pos.y > WINSIZE_Y || pos.x + mSize.x < 0 || pos.y + mSize.y < 0)
	{
		ResetRenderOption();
		return;
	}
	if (mAngle != 0)
	{
		int a = 100;
	}
	D2D1_POINT_2F center_Pos = {pos.x, pos.y };

	//angle������ �������� ȸ�� ��� ���� 
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(mAngle, center_Pos);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF(mFrameInfo[frame].x, mFrameInfo[frame].y,
		(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(mFrameInfo[frame].y + mFrameInfo[frame].height));

	//������� ����
	D2DRENDER->GetRenderTarget()->SetTransform(rotation);

	//������ ��û
	D2DRENDER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);

	this->ResetRenderOption();
}
/********************************************************************************
## ResetRenderOption ##
�̹��� Ŭ���� ���� ���� �ɼǵ� ���� �ʱ�ȭ
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;
	this->mIsReverseAxisX = this->mIsReverseAxisY = false;
	this->mAngle = 0.f;
	D2D1::Matrix3x2F rotationReset = D2D1::Matrix3x2F::Rotation(0.f);
	D2DRENDER->GetRenderTarget()->SetTransform(rotationReset);
	
}

bool CursorOnOff = true;