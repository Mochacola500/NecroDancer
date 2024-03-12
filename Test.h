#pragma once
#include "Scene.h"

class Test : public Scene
{
private:
	MapEditor m_MapEditor;


public:
	Test() = default;
	~Test() = default;

	void Start() override;
	void End() override;

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

};

