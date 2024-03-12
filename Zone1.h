#pragma once
#include "Scene.h"
class Zone1 :
	public Scene
{
private:
	BeatManager  m_beat;
	HeartManager m_heart;

public:
	Zone1() = default;
	~Zone1() = default;

	void Start() override;
	void End() override;

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

