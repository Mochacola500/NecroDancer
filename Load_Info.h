#pragma once

namespace NecroMinecraft
{
	///////////////////////////////////////////////
	//로드아이템 종류
	enum class LOAD_KIND
	{
		RESOUCE_KIND_IMAGE,			//일반 이미지
		RESOUCE_KIND_FRAME_IMAGE,	//프레임 이미지
		RESOUCE_KIND_SOUND,			//사운드
		RESOUCE_KIND_SCENE,			//씬
	};

	///////////////////////////////////////////////
	// 자원
	class LoadResource
	{
	protected:
		string m_keyName;
		wstring m_filePath;
		LOAD_KIND m_loadKind;

	public:
		/* 자원 / 이름 / 종류 반환 */
		virtual LOAD_KIND GetResouceType();
		virtual string GetName();
		virtual wstring GetNameWString();
		virtual wstring GetFilePath();
		virtual string GetFilePathString();

		LoadResource() = default;
		virtual ~LoadResource() = default;
	};

	///////////////////////////////////////////////
	// 로딩 구조체
	struct ImageLoad
	{
		int m_frameX;     // X 프레임 개수
		int m_frameY;     // Y 프레임 개수
	};

	struct SoundLoad
	{
		bool m_bgm;		  // 브금인지 여부
		bool m_loop;		  // 루프인지 여부
	};

	struct SceneLoad
	{
		Scene* m_scene;     // 씬 주소
	};

	///////////////////////////////////////////////
	// 리소스 객체
	struct ImageResouce
		: public LoadResource
	{
		void Init(string keyName, wstring filePath);
	};

	struct FrameImageResouce
		: public LoadResource
	{
		ImageLoad m_resource;
		void Init(string keyName, wstring filePath, int frameX, int frameY);
	};

	struct SoundResource
		: public LoadResource
	{
		SoundLoad m_resource;
		void Init(string keyName, string filePath, bool bgm, bool loop);
	};

	struct SceneResource
		: public LoadResource
	{
		SceneLoad m_resource;
		void Init(string keyName, Scene* scene);
	};
}