#include "stdafx.h"
#include "Game.h"

int Game::GameProcess()
{
	DEBUG_TEXT(DEBUG_YELLOW, "//// Game Process start");
	this->Init();
	this->Run();
	this->Release();
	system("pause");
	return static_cast<int>(mMessage.wParam);
}

void Game::Init()
{
	DEBUG_TEXT(DEBUG_YELLOW, "//// Game Initailize Start");
	srand(GetTickCount64());
	MyWindow::Create();
	Input::Create();
	D2DRenderer::Create();
	ImageManager::Create();
	Camera::Create();
	Camera::Get()->Init();
	Timer::Create();
	SoundManager::Create();
	SceneManager::Create();
	SceneManager::Get()->SceneInit();
	Data::Create();
	UI::Create();
	ObjectManager::Create();
	Inventory::Create();
	ShowCursor(false);
}

void Game::Release()
{
	DEBUG_TEXT(DEBUG_YELLOW, "//// Game Memory Release Start");
	SceneManager::Get()->SceneRelease();
	SceneManager::Delete();
	SoundManager::Delete();
	Timer::Delete();
	Camera::Delete();
	ImageManager::Get()->DeleteAll();
	ImageManager::Delete();
	D2DRenderer::Delete();
	Input::Delete();
	MyWindow::Delete();
	Data::Delete();
	UI::Delete();
	ObjectManager::Get()->Release();
	ObjectManager::Delete();
	Inventory::Delete();
	ShowCursor(true);
}

void Game::Run()
{
	while (true)
	{
		if (PeekMessage(&mMessage, NULL, 0, 0, PM_REMOVE))
		{
			if (mMessage.message == WM_QUIT) break;

			TranslateMessage(&mMessage);
			DispatchMessage(&mMessage);
		}
		else
		{
			TIME->Update();
			KEY->Update();
			CAMERA->Update();
			SCENE->Update();
			SOUND->Update();
			SCENE->Render();
		}
	}

}
