#pragma once
class Image final
{
public:
	struct TagLoadedImageInfo
	{
		string key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const string& key, const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};

private:
	ID2D1Bitmap*		mBitmap;
	float				mAlpha;

	Vector2	mSize;
	float				mScale;
	float				mAngle;

	TagLoadedImageInfo	mLoadInfo;

	vector<Image::FrameRect>	mFrameInfo;
	int							mMaxFrameX;
	int							mMaxFrameY;

	bool						mIsReverseAxisX;
	bool						mIsReverseAxisY;
public:
	Image() = default;
	Image(ID2D1Bitmap*const bitmap, const TagLoadedImageInfo& loadinfo, float alpha = 1.0f, float angle = 0.0f);
	Image(ID2D1Bitmap* bitmap, const TagLoadedImageInfo& loadinfo, const int& maxFrameX, const int& maxFrameY, float alpha = 1.0f, float angle = 0.0f);
	virtual ~Image();
public:
	const Image& operator = (const Image& image) = delete;
	void Render(int x, int y, const bool& isRelative = false);
	void Render(Vector2 pos, const bool& isRelative = false);
	void Render(Vector2 pos, Vector2 index, const bool& isRelative = false);
	void FrameRender(Vector2 pos, Vector2 frameXY, const bool& isRelative = false, float alpha = 1.0f);

	void ResetRenderOption();

	void SetSize(const Vector2& vec) { this->mSize = vec; }
	void SetAlpha(const float& alpha) { this->mAlpha = alpha; }
	void SetScale(const float& scale) { this->mScale = scale; }
	void SetAngle(const float& angle) { this->mAngle = angle; }
	void SetReverseX(const bool& x) { this->mIsReverseAxisX = x; }
	void SetReverseY(const bool& y) { this->mIsReverseAxisY = y; }

	 int GetMaxFrameX()const { return mMaxFrameX; }
	 int GetMaxFrameY()const { return mMaxFrameY; }
	 string GetKey() const { return this->mLoadInfo.key; }
	 UINT GetWidth() const { return mBitmap->GetPixelSize().width; }
	 UINT GetHeight()const { return mBitmap->GetPixelSize().height; }
	 Vector2 GetSize()const { return this->mSize; }
	 Vector2 GetFrameSize(const int& frame = 0) const { Vector2 temp(mFrameInfo[frame].width, mFrameInfo[frame].height); return temp; }
	 TagLoadedImageInfo GetLoadInfo() const { return mLoadInfo; }
};

extern bool CursorOnOff;

