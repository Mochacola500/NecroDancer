#pragma once
#include "Loading.h"

#define LOADING_THREAD_COUNT 10

class LoadingScene : public Scene
{
private:
	Loading* _loading[LOADING_THREAD_COUNT];
	wstring mCurrentImageName;
	FloatRect mBack;
	FloatRect mProgressBar;
	int mPercent;
	float alpha;
	int count;
	int doneCount;
	Image* image;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	void Start() override {};
	void End() override {};
	
	void StreamLoadImage(string text, int index);
	void StreamLoadFrameImage(string text, int index);
	void StreamLoadSound(string text, int index);

	void LoadingImage();
	void LoadingSound();

	LoadingScene() = default;
	~LoadingScene() = default;
};

