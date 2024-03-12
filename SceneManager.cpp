#include "stdafx.h"
#include "SceneManager.h"
#include "Mainmenu.h"

/**************************************
@ 현재 씬 첫 로드 초기화
***************************************/
void SceneManager::SceneInit()
{
	this->AddScene("Test", new Test);
	this->AddScene("Loading", new LoadingScene);
	this->AddScene("Mainmenu", new Mainmenu);
	this->AddScene("Zone1", new Zone1);
	this->ChangeScene("Loading");
	
}

/**************************************
@ 모든 씬 해제
***************************************/
void SceneManager::SceneRelease()
{
	for (auto x : mSceneList)
	{
		x.second->SceneEnd();
		SAFE_DELETE(x.second);
		DEBUG_CONFIRM("Scene delete ", x.second, false);
		DEBUG_TEXT(DEBUG_LIGHT_WHITE," deleted Scene Name is " + x.first);
	}
}

/**************************************
@ 현재 씬 초기화
***************************************/
void SceneManager::Init()
{
	mCurrnetScene->Init();
}

/**************************************
@ 현재 씬 업데이트
***************************************/
void SceneManager::Update()
{
	mCurrnetScene->Update();
}

/**************************************
@ 현재 씬 렌더링
***************************************/
void SceneManager::Render()
{
	D2DRENDER->BeginRender();
	mCurrnetScene->Render();
	TIME->Render();
	D2DRENDER->EndRender();
}

/**************************************
@ 현재 씬 메모리 해제
***************************************/
void SceneManager::Release()
{
	mCurrnetScene->Release();
}

/**************************************
@ 현재 씬을 다음 씬으로 변경
***************************************/
bool SceneManager::ChangeScene(const std::string& sceneName)
{
	DEBUG_TEXT(DEBUG_YELLOW, "//// Scene change start");
	mSceneIter = mSceneList.find(sceneName);
	
	if (mSceneIter != mSceneList.end() &&
		mSceneIter->second != mCurrnetScene)
	{
		if (mCurrnetScene != nullptr) 
		{
			this->Release();
		}

		DEBUG_TEXT(DEBUG_LIGHT_WHITE,"Current scene name is " + mSceneIter->first);
		mCurrnetScene = mSceneIter->second;

		mCurrnetScene->SceneStart();
		mCurrnetScene->Init();
		return true;
	}
	return false;
}

/**************************************
@ 씬 추가
***************************************/
bool SceneManager::AddScene(const std::string& sceneName, Scene* scene)
{
	mSceneIter = mSceneList.find(sceneName);
	if (mSceneIter == mSceneList.end())
	{
		mSceneList.insert(make_pair(sceneName, scene));
		return true;
	}
	return false;
}
