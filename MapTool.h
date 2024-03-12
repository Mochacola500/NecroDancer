#pragma once
#include "Scene.h"
class MapTool :
	public Scene
{
public:
	MapTool() = default;
	~MapTool() = default;

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	Fade m_fade;
};

