#include "stdafx.h"
#include "Test.h"

void Test::Start()
{

}

void Test::End()
{

}

void Test::Init()
{
	OBJECT->Init("", "");
	inGame = false;
	m_MapEditor.Init();
	CAMERA->SetState(CAMERA_STATE::FREE);
	SOUND->Play("lobby_1", 0.5f);
}

void Test::Release()
{
	OBJECT->Release();
	m_MapEditor.Release();
	SOUND->Stop("lobby_1");
}

void Test::Update()
{
	m_MapEditor.Update();
}

void Test::Render()
{
	OBJECT->Render();
	m_MapEditor.Render();
	IMAGE->FindImage("cursor")->SetSize(Vector2(40, 40));
	IMAGE->FindImage("cursor")->Render(_ptMouse);
}


