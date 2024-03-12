#include "stdafx.h"
#include "MapTool.h"

void MapTool::Init()
{
	this->m_fade.Initialize(FADE_OUT);
	CAMERA->SetState(CAMERA_STATE::FREE);

}

void MapTool::Release()
{
}

void MapTool::Update()
{
	m_fade.Update();
}

void MapTool::Render()
{
	m_fade.Render();
}
