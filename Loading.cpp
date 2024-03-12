#include "stdafx.h"
#include "Loading.h"
//=============================================================
//	## loadItem ## (로드아이템 클래스)
//=============================================================


//▼일반 이미지 초기화
HRESULT LoadItem::Init(std::string keyName, std::wstring fileName)
{
	//▼종류, 상세정보 초기화
	_kind = LOAD_KIND::LOAD_KIND_IMAGE;
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//▼프레임 이미지 초기화
HRESULT LoadItem::Init(std::string keyName, std::wstring fileName,int frameX, int frameY)
{
	//▼종류, 상세정보 초기화
	_kind = LOAD_KIND::LOAD_KIND_FRAMEIMAGE;
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//▼사운드 초기화
HRESULT LoadItem::Init(std::string keyName, std::string fileName, bool bgm, bool loop)
{
	//▼종류, 상세정보 초기화
	_kind = LOAD_KIND::LOAD_KIND_SOUND;
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//=============================================================
//	## loading ## (로딩 클래스)
//=============================================================

//▼본인이 추가하고 싶다면 여기에 "이미지매니저"를 통해 로딩에 쓸 백그라운드 및 이미지 추가
void Loading::Init()
{	

	_currentGauge = 0; 
}

//▼만약 뉴할당 받은것들이 존재하면 풀어줌
void Loading::Release()
{
	for (auto &a : _vLoadItem) SAFE_DELETE(a);
}

void Loading::Update()
{
}

void Loading::Render()
{

}

//▼일반 이미지 로딩하기 위해 이닛시키고 담아둠
void Loading::LoadImg(std::string keyName, std::wstring fileName)
{
	LoadItem* item = new LoadItem;
	item->Init(keyName, fileName);
	_vLoadItem.push_back(item);
}

//▼프레임 이미지 로딩하기 위해 이닛시키고 담아둠
void Loading::LoadFrameImage(std::string keyName, std::wstring fileName,int frameX, int frameY)
{
	LoadItem* item = new LoadItem;
	item->Init(keyName, fileName,frameX, frameY);
	_vLoadItem.push_back(item);
}

//▼사운드 로딩하기 위해 이닛시키고 담아둠
void Loading::LoadSound(std::string keyName, const char * fileName, bool bgm, bool loop)
{
	LoadItem * item = new LoadItem;
	item->Init(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL Loading::LoadingDone()
{
	//로딩완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	thread t1(&Loading::LoadingWork, this);

	t1.join();

	//현재 게이지 증가
	_currentGauge++;

	return false;
}

void Loading::LoadingWork()
{
	LoadItem* item = _vLoadItem[_currentGauge];
	switch (item->GetLoadingKind())
	{
	case LOAD_KIND::LOAD_KIND_IMAGE:
	{
		tagImageResource img = item->GetImageResource();
		IMAGE->AddImage(img.keyName, img.fileName);
	}
	break;
	case LOAD_KIND::LOAD_KIND_FRAMEIMAGE:
	{
		tagImageResource img = item->GetImageResource();
		IMAGE->AddFrameImage(img.keyName, img.fileName, img.frameX, img.frameY);
	}
	break;
	case LOAD_KIND::LOAD_KIND_SOUND:
	{
		tagSoundResource snd = item->GetSoundResource();
		SOUND->AddSound(snd.keyName, snd.fileName, snd.bgm, snd.loop);
	}
	break;
	case LOAD_KIND::LOAD_KIND_SCENE:
	{
		tagSceneResource scene = item->GetSceneResource();
		SCENE->AddScene(scene.sceneName, scene.scene);
	}
	break;
	}
}

wstring Loading::GetCurrentLoadName()
{
	if (_currentGauge < _vLoadItem.size())
	{
		wstring name = _vLoadItem[_currentGauge]->GetName();
		return name;
	}
	return L" - 로딩 완료 - ";
}


