#include "stdafx.h"
#include "LoadingThread.h"
namespace NecroMinecraft
{

	LoadingThread::LoadingThread(vector<LoadResource*> loadingSchedule, Vector2 location)
		: m_thread(new thread)                  
		, m_LoadingSchedule(loadingSchedule)
		, m_layout(nullptr)
		, m_location(location)
		, m_currentWorkIndex(0)
	{}

	LoadingThread::~LoadingThread()
	{
		SAFE_DELETE(m_thread);
	}

	bool LoadingThread::LoadingDone()
	{
		//로딩완료됨
		if (m_currentWorkIndex >= m_LoadingSchedule.size())
		{
			return true;
		}

		(*m_thread) = thread([&]() {LoadingProcess(); });
		(*m_thread).join();

		m_currentWorkIndex++;
		return false;
	}


	void LoadingThread::LoadingProcess()
	{
		auto item = m_LoadingSchedule[m_currentWorkIndex];

		switch (item->GetResouceType())
		{
		case LOAD_KIND::RESOUCE_KIND_IMAGE:
		{
			IMAGE->AddImage(item->GetName(), item->GetFilePath());
		}
		break;
		case LOAD_KIND::RESOUCE_KIND_FRAME_IMAGE:
		{
			FrameImageResouce* frameImage = reinterpret_cast<FrameImageResouce*>(item);
			IMAGE->AddFrameImage(item->GetName(), item->GetFilePath(),

				frameImage->m_resource.m_frameX,
				frameImage->m_resource.m_frameY
			);
		}
		break;
		case LOAD_KIND::RESOUCE_KIND_SOUND:
		{
			SoundResource* frameImage = reinterpret_cast<SoundResource*>(item);
			SOUND->AddSound(item->GetName(), item->GetFilePathString(),

				frameImage->m_resource.m_bgm,
				frameImage->m_resource.m_loop
			);
		}
		break;
		case LOAD_KIND::RESOUCE_KIND_SCENE:
		{
			SceneResource* frameImage = reinterpret_cast<SceneResource*>(item);
			SCENE->AddScene(item->GetName(),

				frameImage->m_resource.m_scene
			);
		}
		break;
		}
	}

	void LoadingThread::Render()
	{
		D2DRENDER->LayOutMake(&m_layout, GetCurrentLoadingItem(), 20.0f);
		D2DRENDER->RenderText(m_location, m_layout,ColorF::White);
	}

	//////////////////////////////////////////////
	// 현재 로딩 중인 아이템 출력
	wstring LoadingThread::GetCurrentLoadingItem()
	{
		if (m_currentWorkIndex < m_LoadingSchedule.size()) {
			wstring name = L" thread : " + m_LoadingSchedule[m_currentWorkIndex]->GetNameWString();
			return name;
		}
		return L" thread : 로딩 완료 ";
	}
}