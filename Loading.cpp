#include "stdafx.h"
#include "Loading.h"
//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================


//���Ϲ� �̹��� �ʱ�ȭ
HRESULT LoadItem::Init(std::string keyName, std::wstring fileName)
{
	//������, ������ �ʱ�ȭ
	_kind = LOAD_KIND::LOAD_KIND_IMAGE;
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//�������� �̹��� �ʱ�ȭ
HRESULT LoadItem::Init(std::string keyName, std::wstring fileName,int frameX, int frameY)
{
	//������, ������ �ʱ�ȭ
	_kind = LOAD_KIND::LOAD_KIND_FRAMEIMAGE;
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//����� �ʱ�ȭ
HRESULT LoadItem::Init(std::string keyName, std::string fileName, bool bgm, bool loop)
{
	//������, ������ �ʱ�ȭ
	_kind = LOAD_KIND::LOAD_KIND_SOUND;
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;
	name.assign(keyName.begin(), keyName.end());
	return S_OK;
}

//=============================================================
//	## loading ## (�ε� Ŭ����)
//=============================================================

//�庻���� �߰��ϰ� �ʹٸ� ���⿡ "�̹����Ŵ���"�� ���� �ε��� �� ��׶��� �� �̹��� �߰�
void Loading::Init()
{	

	_currentGauge = 0; 
}

//�常�� ���Ҵ� �����͵��� �����ϸ� Ǯ����
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

//���Ϲ� �̹��� �ε��ϱ� ���� �̴ֽ�Ű�� ��Ƶ�
void Loading::LoadImg(std::string keyName, std::wstring fileName)
{
	LoadItem* item = new LoadItem;
	item->Init(keyName, fileName);
	_vLoadItem.push_back(item);
}

//�������� �̹��� �ε��ϱ� ���� �̴ֽ�Ű�� ��Ƶ�
void Loading::LoadFrameImage(std::string keyName, std::wstring fileName,int frameX, int frameY)
{
	LoadItem* item = new LoadItem;
	item->Init(keyName, fileName,frameX, frameY);
	_vLoadItem.push_back(item);
}

//����� �ε��ϱ� ���� �̴ֽ�Ű�� ��Ƶ�
void Loading::LoadSound(std::string keyName, const char * fileName, bool bgm, bool loop)
{
	LoadItem * item = new LoadItem;
	item->Init(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL Loading::LoadingDone()
{
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	thread t1(&Loading::LoadingWork, this);

	t1.join();

	//���� ������ ����
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
	return L" - �ε� �Ϸ� - ";
}


