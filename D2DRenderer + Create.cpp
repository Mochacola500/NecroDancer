#include "stdafx.h"
#include "D2DRenderer.h"
/*****************************************************
# �⺻ �귯�� ����
*******************************************************/
void D2DRenderer::CreateDefaultBrush()
{
	mD2DRender->CreateSolidColorBrush(D2D1::ColorF(ColorF::Black, 1.0f), &mCommonBrush);
}
/*****************************************************
# AddTextFormat 
@@ wstring font : ��Ʈ��
@@ float defaultSize : ��Ʈ ������ = 1.f
*******************************************************/
void D2DRenderer::AddTextFormat(wstring font, float defaultSize)
{
	mFontIter = mFontList.find(font);
	if (mFontIter == mFontList.end())
	{
		IDWriteTextFormat* format = NULL;

		ASSERT_HRESULT_CHECK(
			this->mDWFactory->CreateTextFormat(
				font.c_str(), NULL,
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				defaultSize,
				L"ko",
				&format
			));

		this->mFontList.insert(make_pair(font, format));
	}
}
/*****************************************************
# LayOutMake
@ layout : ������ ���̾�
@ text   : ����� ����
@ size   : ��Ʈ ũ��
@ font   : ����� ��Ʈ
*******************************************************/
void D2DRenderer::LayOutMake(IDWriteTextLayout** layout, wstring text, float size,
	DWRITE_TEXT_ALIGNMENT align, wstring font)
{
	(*layout) = nullptr;
		this->mDWFactory->CreateTextLayout(
			text.c_str()
			, (UINT32)text.length()
			, this->mFontList[font]
			, text.length() * size
			, size
			, layout);
	
	// �ؽ�Ʈ ��� ���� ����
	mRange.startPosition = 0;
	mRange.length = (UINT32)text.length();

	(*layout)->SetFontSize(size, mRange);
	(*layout)->SetTextAlignment(align);
}