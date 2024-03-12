#pragma once
#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	/***********************************
	@ Start : ���� ù ����� ���� 
	@ End   : ���α׷� ����� ����
	************************************/
	// Start �Լ��� SceneManager���� �� ��ȯ�� ��� �ȴ�.
	// End �Լ��� ���α׷� ����� ����ȴ�.
	virtual void Start() = 0;   
	virtual void End() = 0;     

	/***********************************
	@ Init    : �ٸ� ������ �ش� ������ ��ȯ�� ����
	@ Release : �ش� ������ �ٸ� ������ ��ȯ�� ����
	@ Update  : �ش� ���Ͻ� �� ���� ���� ����
	@ Rnder   : �ش� ���Ͻ� �� ���� ���� ����
	************************************/
	// Init�� Release�� SceneManager���� �� ��ȯ�� ��� �ȴ�.
	// Update�� Render�� Game Class�� Run �Լ����� ��� �ȴ�.
	virtual void Init() = 0;     
	virtual void Release() = 0;
	virtual void Update() = 0;  
	virtual void Render() = 0;  

	/***********************************
	@ SceneStart  : ���� ù ����� Start �Լ� ����
	@ SceneEnd    : ���α׷� ����� End �Լ� ����
	@ SetLoading  : ���ӿ� �ʿ��� �ε� ����
	@ LoadingCall : ���ӿ� �ʿ��� ������ �ε� 
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
	bool mStartedOnce;      // 1���̶� ������ �Ǿ��°�?
};
#endif // !SCENE_H
