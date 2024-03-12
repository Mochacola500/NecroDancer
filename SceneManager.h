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
	// 씬 변경 및 추가
	bool ChangeScene(const std::string& sceneName);
	bool AddScene(const std::string& sceneName, Scene* scene);

	// 전체 씬 추가 및 해제
	void SceneInit();
	void SceneRelease();

	// 현재 루프 씬 초기화,업데이트,렌더링
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