#include "stdafx.h"
#include "ImageManager.h"

#include "Image.h"
ImageManager::ImageManager()
	:mWicFactory(nullptr)
{
	//WIC 팩토리 생성
	//Windows Imaging Component
	//Direct2D는 이미지를 로드하는 기능이 없다. 
	//고로 Direct2D는 WIC라는 라이브러리의 이미지로부터 이미지 데이터를 만들 수 있다.
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}

/*********************************************************************
## ImageManager ##
**********************************************************************/
ImageManager::~ImageManager()
{
	this->DeleteAll();
	SAFE_RELEASE(mWicFactory);
}
/*********************************************************************
## AddImage ##
**********************************************************************/
Image * ImageManager::AddImage(const string& key, const wstring& file)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = this->CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo);
		mImageList.insert(make_pair(key, image));
		return image;
	}
	else
		assert(E_FAIL);

	return nullptr;
}
/*********************************************************************
## AddFrameImage ##
**********************************************************************/
Image * ImageManager::AddFrameImage(const string& key, const wstring& file, const int& maxFrameX, const int& maxFrameY)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo, maxFrameX, maxFrameY);
		this->mImageList.insert(make_pair(key, image));
		return image;
	}

	return nullptr;
}
/*********************************************************************
## FindImage ##
**********************************************************************/
Image * ImageManager::FindImage(const string& key)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
		return iter->second;
	return nullptr;
}
/*********************************************************************
## CreateD2DBitmapFromFile ##
@@ wstring file : 파일 경로
**********************************************************************/
ID2D1Bitmap * ImageManager::CreateD2DBitmapFromFile(const wstring & file)
{
	//디코더 생성
	IWICBitmapDecoder* ipDecoder = nullptr;

	ASSERT_HRESULT_CHECK(mWicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder));

	//디코더에서 프레임얻음
	IWICBitmapFrameDecode* ipFrame = nullptr;
	ASSERT_HRESULT_CHECK(ipDecoder->GetFrame(0, &ipFrame));

	//프레임을 기반으로 포맷 컨버터 생성
	IWICFormatConverter* convertedSrcBmp = nullptr;
	ASSERT_HRESULT_CHECK(hr = mWicFactory->CreateFormatConverter(&convertedSrcBmp));

	//컨버터 초기화
	ASSERT_HRESULT_CHECK(convertedSrcBmp->Initialize
	(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	));

	//컨버트된 데이터를 기반으로 실제 Direct2D용 비트맵을 생성
	ID2D1Bitmap* ipResult = nullptr;
	ASSERT_HRESULT_CHECK(D2DRENDER->GetRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	));

	SAFE_RELEASE(convertedSrcBmp);
	SAFE_RELEASE(ipFrame);
	SAFE_RELEASE(ipDecoder);

	return ipResult;
}
/*********************************************************************
## DeleteAll ##
**********************************************************************/
void ImageManager::DeleteAll()
{
	SAFE_DELETE_MAP(mImageList);
}
