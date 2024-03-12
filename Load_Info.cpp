#include "stdafx.h"
#include "Load_Info.h"

namespace NecroMinecraft
{
	LOAD_KIND LoadResource::GetResouceType()
	{
		return this->m_loadKind;
	}

	string LoadResource::GetName()
	{
		return this->m_keyName;
	}

	wstring LoadResource::GetNameWString()
	{
		wstring Get = L"";
		Get.assign(m_filePath.begin(), m_filePath.end());
		return Get;
	}

	wstring LoadResource::GetFilePath()
	{
		return m_filePath;
	}

	string LoadResource::GetFilePathString()
	{
		string Get = "";
		Get.assign(m_filePath.begin(), m_filePath.end());
		return Get;
	}

	void ImageResouce::Init(string keyName, wstring filePath)
	{
		this->m_keyName = keyName;
		this->m_filePath = filePath;
		this->m_loadKind = LOAD_KIND::RESOUCE_KIND_IMAGE;
	}

	void FrameImageResouce::Init(string keyName, wstring filePath, int frameX, int frameY)
	{
		this->m_keyName = keyName;
		this->m_filePath = filePath;
		this->m_loadKind = LOAD_KIND::RESOUCE_KIND_FRAME_IMAGE;
		this->m_resource.m_frameX = frameX;
		this->m_resource.m_frameY = frameY;
	}


	void SoundResource::Init(string keyName, string filePath, bool bgm, bool loop)
	{
		this->m_keyName = keyName;
		this->m_filePath.assign(filePath.begin(), filePath.end());
		this->m_loadKind = LOAD_KIND::RESOUCE_KIND_SOUND;
		this->m_resource.m_bgm = bgm;
		this->m_resource.m_loop = loop;
	}

	void SceneResource::Init(string keyName, Scene* scene)
	{
		this->m_keyName = keyName;
		this->m_loadKind = LOAD_KIND::RESOUCE_KIND_SCENE;
		this->m_resource.m_scene = scene;
	}
}
