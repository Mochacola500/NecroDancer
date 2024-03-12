#include "stdafx.h"
#include "BeatManager.h"


void BeatManager::Init(string fileName)
{
	this->fileName = fileName;
	m_Current_Beat = 0.f;
	m_Beat_Speed = 8.0f;

	ifstream loadBeat("data/music/" + fileName + ".txt");
	SOUND->Play(fileName, 0.2f);

	string beat_bit_string;
	
	while (loadBeat >> beat_bit_string) 
	{
		m_Beat_Frames.push_back(atoi(beat_bit_string.c_str()));
	}
}

void BeatManager::AttachManagers(ObjectManager* tileManager, HeartManager * heartManager)
{
	this->m_heart = heartManager;
	this->m_tiles = tileManager;

	CreateBar();
}

void BeatManager::CreateBar()
{
	for (size_t i = 0; i < m_Beat_Frames.size(); ++i) {
		m_heart->CreateBit((m_Beat_Frames[i] / 2));
	}
}


void BeatManager::Update()
{
	if (m_Beat_Frames.size())
	{
		if (m_heart->dodo == true) {
			m_heart->dodo = false;
			this->Active();
			
		}

		if (m_Beat_Frames.front() < m_Current_Beat * 2)
		{
			this->Active();
		}

		m_Current_Beat += m_Beat_Speed;
	}
	else
	{
		Init(this->fileName);
		CreateBar();
	}
}

void BeatManager::Active()
{
	m_tiles->BinaryImageLocation();
	m_tiles->TileUpdate();
	m_tiles->MonsterUpdate();
	m_Beat_Frames.erase(m_Beat_Frames.begin());
	UI::Get()->ValueUp();
}

void BeatManager::Release()
{
	m_Beat_Frames.clear();
	SOUND->Stop(fileName);
}

