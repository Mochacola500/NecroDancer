#pragma once
namespace NecroMinecraft
{
	class LoadingThread
	{
	public:
		LoadingThread(vector<LoadResource*> loadingSchedule, Vector2 location);
		~LoadingThread();

		///////////////////////////////////////
		// 로딩 실행
		bool LoadingDone();
		void LoadingProcess();

		void Render();

		///////////////////////////////////////
		// 현재 로딩 중인 내역 출력
		wstring GetCurrentLoadingItem();

	private:
		thread* m_thread;
		int m_currentWorkIndex;
		vector<LoadResource*> m_LoadingSchedule;
		IDWriteTextLayout* m_layout;
		Vector2 m_location;
	};
}