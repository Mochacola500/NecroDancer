#include "stdafx.h"
#include "SceneManager.h"
#include "Mainmenu.h"

/**************************************
@ ���� �� ù �ε� �ʱ�ȭ
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
@ ��� �� ����
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
@ ���� �� �ʱ�ȭ
***************************************/
void SceneManager::Init()
{
	mCurrnetScene->Init();
}

/**************************************
@ ���� �� ������Ʈ
***************************************/
void SceneManager::Update()
{
	mCurrnetScene->Update();
}

/**************************************
@ ���� �� ������
***************************************/
void SceneManager::Render()
{
	D2DRENDER->BeginRender();
	mCurrnetScene->Render();
	TIME->Render();
	D2DRENDER->EndRender();
}

/**************************************
@ ���� �� �޸� ����
***************************************/
void SceneManager::Release()
{
	mCurrnetScene->Release();
}

/**************************************
@ ���� ���� ���� ������ ����
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
@ �� �߰�
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
