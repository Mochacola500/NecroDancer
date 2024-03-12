#pragma once
namespace NecroMinecraft
{
	class LoadingThread
	{
	public:
		LoadingThread(vector<LoadResource*> loadingSchedule, Vector2 location);
		~LoadingThread();

		///////////////////////////////////////
		// �ε� ����
		bool LoadingDone();
		void LoadingProcess();

		void Render();

		///////////////////////////////////////
		// ���� �ε� ���� ���� ���
		wstring GetCurrentLoadingItem();

	private:
		thread* m_thread;
		int m_currentWorkIndex;
		vector<LoadResource*> m_LoadingSchedule;
		IDWriteTextLayout* m_layout;
		Vector2 m_location;
	};
}