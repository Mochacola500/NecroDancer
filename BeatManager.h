#pragma once
class BeatManager
{
public:
	void Init(string fileName = "");
	void AttachManagers(ObjectManager* tileManager, HeartManager* heartManager);

	void CreateBar();

	void BeatScale(float scale) { m_Beat_Speed = scale; }

	void Update();
	void Active();

	void Release();

	BeatManager() = default;
	~BeatManager() = default;



	float m_Beat_Speed;
private:
	string fileName;
	ObjectManager* m_tiles;
	HeartManager* m_heart;
	int count;

	vector<int> m_Beat_Frames;
	float m_Current_Beat;
};


