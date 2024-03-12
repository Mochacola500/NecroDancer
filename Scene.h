#pragma once
#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	/***********************************
	@ Start : 씬의 첫 실행시 실행 
	@ End   : 프로그램 종료시 실행
	************************************/
	// Start 함수는 SceneManager에서 씬 전환시 사용 된다.
	// End 함수는 프로그램 종료시 실행된다.
	virtual void Start() = 0;   
	virtual void End() = 0;     

	/***********************************
	@ Init    : 다른 씬에서 해당 씬으로 전환시 실행
	@ Release : 해당 씬에서 다른 씬으로 전환시 실행
	@ Update  : 해당 씬일시 매 루프 마다 실행
	@ Rnder   : 해당 씬일시 매 루프 마다 실행
	************************************/
	// Init과 Release는 SceneManager에서 씬 전환시 사용 된다.
	// Update와 Render는 Game Class의 Run 함수에서 사용 된다.
	virtual void Init() = 0;     
	virtual void Release() = 0;
	virtual void Update() = 0;  
	virtual void Render() = 0;  

	/***********************************
	@ SceneStart  : 씬의 첫 실행시 Start 함수 실행
	@ SceneEnd    : 프로그램 종료시 End 함수 실행
	@ SetLoading  : 게임에 필요한 로딩 설정
	@ LoadingCall : 게임에 필요한 내용을 로딩 
	************************************/
	virtual void SceneStart() final 
	{
		if (!mStartedOnce)
		{
			this->mStartedOnce = true;
			this->Start();
		}
	};

	virtual void SceneEnd() final
	{
		if (mStartedOnce)
		{
			this->End();
		}
	}

	Scene() :
		mStartedOnce(false)
	{}

	virtual ~Scene() = default;

protected: 
	bool mStartedOnce;      // 1번이라도 실행이 되었는가?
};
#endif // !SCENE_H
