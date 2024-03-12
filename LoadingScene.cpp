#include "stdafx.h"
#include "LoadingScene.h"

void LoadingScene::Init()
{
	//▼로딩클래스 뉴할당 해주고 초기화
	for (int i = 0; i < LOADING_THREAD_COUNT; ++i)
	{
		_loading[i] = new Loading;
		_loading[i]->Init();
	}
	mBack = { 300, WINSIZE_Y - 150 , WINSIZE_X - 300, WINSIZE_Y - 170 };
	//▼이미지 사운드 씬 로딩
	this->LoadingImage();
	this->LoadingSound();

	alpha = 1.f;
	count = 0;
	doneCount = 0;

	image = IMAGE->AddImage("splash_screen", L"data/mainmenu/splash_screen.png");

}

void LoadingScene::Release()
{
	//로딩클래스 뉴할당 해준적 있으니 해제
	SAFE_RELEASE_ARRAY(_loading);
	//SAFE_DELETE_ARRAY(*_loading);
}

//▼업데이트 한번에 하나의 아이템 로딩함. 로딩서 움직이는 이미지 추가해줘도 되고, 로딩씬서 해줘도 되고.
void LoadingScene::Update()
{
	for (int i = 0; i < LOADING_THREAD_COUNT; ++i)
	{
		if (_loading[i]->LoadingDone())
		{
			doneCount++;
		}
		
	}
	if (doneCount == LOADING_THREAD_COUNT) //이프 조건문을 확인하는 동시에 그 아래 있는 함수들까지 실행됨
	{
		//if (count == 0)
		//{
		//	alpha -= 0.05f;
		//	count += 2;
		//	if (alpha < 0)
		//	{
				////////////////////////////////////////////
				// 로딩 완료 후 전환 되는 Scene
		UI::Get()->Init();
		Sleep(100);
		SCENE->ChangeScene("Mainmenu");
				////////////////////////////////////////////
		//	}
		//}
		//else
		//{
		//	count--;
		//}
	}
	else
	{
		mCurrentImageName.clear();
		for (int i = 0; i < LOADING_THREAD_COUNT; ++i)
		{
			mCurrentImageName += _loading[i]->GetCurrentLoadName();
			mCurrentImageName += L"\n";
		}
	}
}

//▼퍼센테이지 화면에 그려줌. 
void LoadingScene::Render()
{
	//Sleep(200);
	D2DRENDER->FillRectangle(FloatRect(0, 0, WINSIZE_X, WINSIZE_Y), ColorF::Black, alpha);

	float num = 0;
	float cur = 0;

	for (int i = 0; i < LOADING_THREAD_COUNT; ++i)
	{
		num += _loading[i]->GetLoadItem().size();
		cur += _loading[i]->GetCurrentGauge();
	}

	mPercent = static_cast<int>(cur / num * 100); // 백분율
	std::wstring str = std::to_wstring(mPercent) + L" %";

	IDWriteTextLayout* percent;
	IDWriteTextLayout* currentLoading;
	mProgressBar = { 300.f, WINSIZE_Y - 150.f ,100.f + mPercent * 10.f, WINSIZE_Y - 170.f };

	if (doneCount != LOADING_THREAD_COUNT)
	{
		D2DRENDER->LayOutMake(&percent, str, 20.f);
		D2DRENDER->LayOutMake(&currentLoading, mCurrentImageName, 20.f);
		D2DRENDER->RenderText(Vector2(WINSIZE_X - 250.f, WINSIZE_Y - 175.f), percent, ColorF::White);
		D2DRENDER->RenderText(Vector2(10.f, 90.f), currentLoading, ColorF::White);
		
		D2DRENDER->FillRectangle(mProgressBar, ColorF::White, 0.6f);
		D2DRENDER->DrawRectangle(mBack, ColorF::WhiteSmoke, 1.0f, 4.0f);

		image->SetSize(Vector2(WINSIZE_X - 600, WINSIZE_Y - 400));
		image->Render(Vector2(300,200));

		SAFE_RELEASE(percent);
		SAFE_RELEASE(currentLoading);
	}
	doneCount = 0;
}

inline void LoadingScene::StreamLoadImage(string text, int index)
{
	ifstream stream(text);

	if (stream)
	{
		string first;
		string end;
		string current;

		stream >> first >> end;

		while (stream >> current)
		{
			string filePath = first + current + end;
			wstring wfilePath;
			this->_loading[index]->LoadImg(current, wfilePath.assign(filePath.begin(), filePath.end()));
		}
	}
}

void LoadingScene::StreamLoadFrameImage(string text, int index)
{
	ifstream stream(text);

	if (stream)
	{
		string first;
		string end;
		string current;
		int indexX;
		int indexY;

		stream >> first >> end;

		while (stream >> current >> indexX >> indexY)
		{
			string filePath = first + current + end;
			wstring wfilePath;
			this->_loading[index]->LoadFrameImage(current, wfilePath.assign(filePath.begin(), filePath.end()), indexX, indexY);
		}
	}
}

void LoadingScene::StreamLoadSound(string text, int index)
{
	ifstream stream(text);

	if (stream)
	{
		string first;
		string end;
		string current;
		bool bgm;
		bool loop;
		stream >> first >> end;

		while (stream >> current >> bgm >> loop )
		{
			string filePath = first + current + end;
			this->_loading[index]->LoadSound(current, filePath.c_str(), bgm,loop);
		}
	}
}

//▼원래 사용하던 이미지 로딩방법
void LoadingScene::LoadingImage()
{
	StreamLoadImage("data/mainmenu/mainmenu.txt", 1);
	StreamLoadFrameImage("data/level/level.txt", 2);
	StreamLoadImage("data/level/level2.txt", 3);
	StreamLoadImage("data/gui/gui.txt", 4);
	StreamLoadFrameImage("data/gui/gui2.txt", 5);
	StreamLoadFrameImage("data/entities/entities.txt", 6);
	StreamLoadFrameImage("data/swipes/swipes.txt", 0);
	StreamLoadFrameImage("data/items/items.txt", 7);
	StreamLoadImage("data/particles/particles.txt", 8);
	StreamLoadSound("data/music.txt", 9);
	StreamLoadSound("data/sounds.txt", 0);
}

void LoadingScene::LoadingSound()
{

}
