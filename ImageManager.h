#pragma once
#include "SingletonBase.h"
class ImageManager final : public SingletonBase<ImageManager>
{
private:
	typedef unordered_map<string, class Image*>::iterator ImageIter;
private:
	unordered_map<string, class Image*> mImageList;

	IWICImagingFactory* mWicFactory;
public:
	ImageManager();
	virtual ~ImageManager();

	class Image* AddImage(const string& key, const wstring& file);
	class Image* AddFrameImage(const string& key, const wstring& file, const int& maxFrameX, const int& maxFrameY);
	class Image* FindImage(const string& key);

	void DeleteAll();
private:
	ID2D1Bitmap* CreateD2DBitmapFromFile(const wstring& file);

};
