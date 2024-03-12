#pragma once
#include "SingletonBase.h"

typedef unordered_map<wstring, IDWriteTextFormat*> FontList;

class D2DRenderer final : public SingletonBase<D2DRenderer>
{
private:
	ID2D1Factory* mD2DFactory;
	IDWriteFactory* mDWFactory;
	void CreateFactory();
	
	ID2D1HwndRenderTarget* mD2DRender;
	void CreateRenderTarget();
	void CreateDefaultBrush();

	FontList mFontList;
	FontList::iterator mFontIter;
	void AddTextFormat(wstring font, float defaultSize = 1.f);

	DWRITE_TEXT_RANGE mRange;
	ID2D1SolidColorBrush* mCommonBrush;

public:
	void BeginRender();
	void EndRender();
	// 레이어 생성
	void LayOutMake(IDWriteTextLayout** layout, wstring text, float size = 1.f,
		DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, wstring font = L"맑은고딕");

	// 렌더 타겟 반환
	ID2D1HwndRenderTarget* GetRenderTarget() const { return this->mD2DRender; }
public:
	// 텍스트 출력
	void RenderText(Vector2 writePosition, IDWriteTextLayout* layout, ColorF::Enum color, float alpha = 1.f);

	// 선, 사각형, 원, 마름모 그리기
	void DrawLine(Vector2 start, Vector2 end, D2D1::ColorF::Enum color, float alpha = 1.f, float strokeWidth = 1.f);
	void DrawRectangle(FloatRect rc, D2D1::ColorF::Enum color, float alpha = 1.f, float strokeWidth = 1.f);
	void DrawEllipse(Vector2 origin, float radius, D2D1::ColorF::Enum color, float alpha = 1.f, float strokeWidth = 1.f);
	void DrawRhombus(Vector2 center, D2D1::ColorF::Enum color, float alpha = 1.f, float strokeWidth = 1.f);
	// 사각형, 원 그리기 fill
	void FillRectangle(FloatRect rc, D2D1::ColorF::Enum color, float alpha = 1.f);
	void FiilEllipse(Vector2 origin, float radius, D2D1::ColorF::Enum color, float alpha = 1.f);

	D2DRenderer();
	virtual ~D2DRenderer();
};
