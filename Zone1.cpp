#include "stdafx.h"
#include "Zone1.h"


void Zone1::Start()
{
}

void Zone1::End()
{
}

void Zone1::Init()
{
	OBJECT->Init("zone1_1_tile.txt", "zone1_1_object.txt");
	inGame = true;
	m_beat.Init("zone1_1");
	m_heart.Init();
	m_beat.AttachManagers(OBJECT, &m_heart);
	CAMERA->SetTarget(OBJECT->mObjectMap[PLAYER][0]);
	CAMERA->SetState(CAMERA_STATE::TARGETE);
}

void Zone1::Release()
{
	OBJECT->Release();
	//m_heart.Release();
	//m_beat.Release();
}

void Zone1::Update()
{
	OBJECT->Update();
	m_beat.Update();
	m_heart.Update();
	UIS->Update();
}

void Zone1::Render()
{
	OBJECT->Render();
	m_heart.Render();
	UIS->Render();
	IMAGE->FindImage("cursor")->SetSize(Vector2(40, 40));
	IMAGE->FindImage("cursor")->Render(_ptMouse);
}
