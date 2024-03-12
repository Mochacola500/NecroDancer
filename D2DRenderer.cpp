#include "stdafx.h"
#include "D2DRenderer.h"

/*****************************************************
## D2DRenderer ##
*******************************************************/
D2DRenderer::D2DRenderer()
	: mD2DFactory(nullptr)
	, mD2DRender(nullptr)
	, mDWFactory(nullptr)
	, mCommonBrush(nullptr)
{
	this->CreateFactory();
	this->CreateRenderTarget();
	this->CreateDefaultBrush();
	this->AddTextFormat(L"맑은고딕");
}

/*****************************************************
## ~D2DRenderer ##
*******************************************************/
D2DRenderer::~D2DRenderer()
{
	SAFE_RELEASE_MAP(mFontList);
	SAFE_RELEASE(mCommonBrush);
	SAFE_RELEASE(mD2DRender);
	SAFE_RELEASE(mDWFactory);
	SAFE_RELEASE(mD2DFactory);
}
/*****************************************************
## BeginRender ##
*******************************************************/
void D2DRenderer::BeginRender()
{
	// 윈도우 보여지는지 체크
	D2D1_WINDOW_STATE eWindowState = this->mD2DRender->CheckWindowState();
	if (!(eWindowState & D2D1_WINDOW_STATE_OCCLUDED))
	{
		mD2DRender->BeginDraw();
		mD2DRender->Clear(ColorF(ColorF::Black, 1.0f));
	}
}
/*****************************************************
## EndRender ##
*******************************************************/
void D2DRenderer::EndRender()
{
	mD2DRender->EndDraw();
}

/*****************************************************
## CreateFactory ##
*******************************************************/
void D2DRenderer::CreateFactory()
{
	ASSERT_HRESULT_CHECK(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED
		, &mD2DFactory));

	ASSERT_HRESULT_CHECK(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED
		, __uuidof(*&mDWFactory)
		, (IUnknown**)(&mDWFactory)));
}
/*****************************************************
## CreateRenderTarget ##
*******************************************************/
void D2DRenderer::CreateRenderTarget()
{
	RECT rc = WINDOW->GetWindowRect();

	ASSERT_HRESULT_CHECK(
		this->mD2DFactory->CreateHwndRenderTarget
		( D2D1::RenderTargetProperties()
		, D2D1::HwndRenderTargetProperties 
		(WINDOW->GetHwnd(), D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top))
		, &this->mD2DRender));
}

