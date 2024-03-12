#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager : public SingletonBase<SceneManager>
{
private:
	std::unordered_map<std::string, Scene*> mSceneList;
	std::unordered_map<std::string, Scene*>::iterator mSceneIter;
	class Scene* mCurrnetScene;

public:
	// �� ���� �� �߰�
	bool ChangeScene(const std::string& sceneName);
	bool AddScene(const std::string& sceneName, Scene* scene);

	// ��ü �� �߰� �� ����
	void SceneInit();
	void SceneRelease();

	// ���� ���� �� �ʱ�ȭ,������Ʈ,������
	void Init();
	void Update();
	void Render();
	void Release();

private:
	friend class SingletonBase<SceneManager>;
	SceneManager() :
		mCurrnetScene(nullptr)
	{}
	~SceneManager() = default;
};

#endif // !SCENE_MANAGER_H