#pragma once

namespace NecroMinecraft
{
	///////////////////////////////////////////////
	//�ε������ ����
	enum class LOAD_KIND
	{
		RESOUCE_KIND_IMAGE,			//�Ϲ� �̹���
		RESOUCE_KIND_FRAME_IMAGE,	//������ �̹���
		RESOUCE_KIND_SOUND,			//����
		RESOUCE_KIND_SCENE,			//��
	};

	///////////////////////////////////////////////
	// �ڿ�
	class LoadResource
	{
	protected:
		string m_keyName;
		wstring m_filePath;
		LOAD_KIND m_loadKind;

	public:
		/* �ڿ� / �̸� / ���� ��ȯ */
		virtual LOAD_KIND GetResouceType();
		virtual string GetName();
		virtual wstring GetNameWString();
		virtual wstring GetFilePath();
		virtual string GetFilePathString();

		LoadResource() = default;
		virtual ~LoadResource() = default;
	};

	///////////////////////////////////////////////
	// �ε� ����ü
	struct ImageLoad
	{
		int m_frameX;     // X ������ ����
		int m_frameY;     // Y ������ ����
	};

	struct SoundLoad
	{
		bool m_bgm;		  // ������� ����
		bool m_loop;		  // �������� ����
	};

	struct SceneLoad
	{
		Scene* m_scene;     // �� �ּ�
	};

	///////////////////////////////////////////////
	// ���ҽ� ��ü
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