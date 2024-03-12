#pragma once
#include "SingletonBase.h"


extern int _ComboStack;
extern bool inGame;

struct Fog
{
	FloatRect m_fill;
	Vector2 m_Location;
	float light;
	bool isOnceOpen;
	bool check;

	Fog(Vector2 location)
	{
		m_Location = location;
		m_fill = { location.x, location.y,
			location.x + TILESIZE_X,
			location.y + TILESIZE_Y };
		light = 1.0f;
		isOnceOpen = false;
		check = false;
	}

	void Render()
	{
		D2DRENDER->FillRectangle(CAMERA->CorrecteLocation(&m_fill), ColorF::Black, light);
	}
};


class Path;

class ObjectManager 
	: public SingletonBase<ObjectManager>
{
public:
	friend class SingletonBase<ObjectManager>;
	void Init(string filename, string filename2);
	void Update();
	void Render();
	void Release();
	void TileUpdate();
	void TileNonComboUpdate();
	void TileComboUpdate();
	bool IsInIndex(int x, int y);
	
	Vector2 GetTileIndex(Object* p) {
		Vector2 temp = p->GetCenter();
		int tempx = static_cast<int>((temp.x + 12) / TILESIZE_X);
		int tempy = static_cast<int>((temp.y + 12) / TILESIZE_Y);
		return Vector2(tempx, tempy);
	}

	Tile * GetTile(Object * p) {
		Vector2 temp = GetTileIndex(p);
		return m_Tiles[(temp.y * mapsizey) + temp.x].get();
	}

	Vector2 GetTileIndex(Vector2 p) {
		int tempx = static_cast<int>((p.x + 12) / TILESIZE_X);
		int tempy = static_cast<int>((p.y + 12) / TILESIZE_Y);
		return Vector2(tempx, tempy);
	}

	Tile* GetTile(Vector2 p) {
		Vector2 temp = GetTileIndex(p);
		if (IsInIndex(temp.x, temp.y)) return nullptr;
		return m_Tiles[(temp.y * mapsizey) + temp.x].get();
	}

	Tile* GetTileMouse(Vector2 p) {
		Vector2 temp = p;
		return m_Tiles[(temp.y * mapsizey) + temp.x].get();
	}

	Vector2 PathFinder(Vector2 start, Vector2 goal);

	// 안개
	void Fill(Object* pos, int count = 5);
	void FillFog(Vector2 pos, int count);

	void SetOwnerCount(int count) { this->mOwnerCount = count; }

	void BinaryImageLocation();
	void ComboRenderImageLocation();

	ObjectManager() = default;
	~ObjectManager() = default;

	bool OnFog(Vector2 pos) {
		int x = static_cast<int>(pos.x / TILESIZE_X);
		int y = static_cast<int>(pos.y / TILESIZE_X);
		if (x > -1 && y > -1 && x < mapsizex && y < mapsizey) {
			if (m_Fogs[y * mapsizey + x].get()->check == false) {
				return true;
			}
		}
		return false;
	}

	// 복사 및 대입 연산 방지
	ObjectManager(const ObjectManager&) = delete;
	const ObjectManager& operator=(const ObjectManager&) = delete;
	
	void AddObject(ObjectType type, Object* p)
	{
		int x = static_cast<int>(p->GetCenter().x / TILESIZE_X);
		int y = static_cast<int>(p->GetCenter().y / TILESIZE_X);

		if (x > -1 && y > -1 && x < mapsizex && y < mapsizey) {
			if (m_Tiles[y * mapsizey + x].get()->p == nullptr) {

				p->objectm = this;
				mObjectMap[type].push_back(p);

				m_Tiles[y * mapsizey + x].get()->p = p;

				mRender.push_back(p);
			}
			else
			{
				SAFE_DELETE(p);
			}
		}
		else
		{
			SAFE_DELETE(p);
		}
	}

	void MonsterUpdate();

	Object* GetObjectPtr(Vector2 index) {
		int x =  static_cast<int>((index.x + 12) / TILESIZE_X);
		int y =  static_cast<int>((index.y + 12) / TILESIZE_X);

		if (x > -1 && y > -1 && x < mapsizex && y < mapsizey) {
			if (m_Tiles[y * mapsizey + x].get()->p == nullptr) {
				return nullptr;
			}
			else
			{
				return m_Tiles[y * mapsizey + x].get()->p;
			}
		}
		return nullptr;
	}

	bool CanMove(Vector2 index, Object* p) {
		int x =  static_cast<int>(index.x / TILESIZE_X);
		int y =  static_cast<int>(index.y / TILESIZE_X);

		if (x > -1 && y > -1 && x < mapsizex && y < mapsizey) {
			Tile* targetTile = m_Tiles[y * mapsizey + x].get();
			if (targetTile->p == nullptr) {

				int xx =  static_cast<int>((p->GetCenter().x + 12) / TILESIZE_X);
				int yy =  static_cast<int>((p->GetCenter().y + 12) / TILESIZE_X);
				m_Tiles[yy * mapsizey + xx]->p = nullptr; // 타일 포인터 제거
				targetTile->p = p; // 갈곳 예약

				if (p->GetPlayer()) {
					if (targetTile->item != nullptr) {
						if (targetTile->item->Meet()) {
							if (targetTile->item->origin == "resource_coin") {
								TextEvent* goldGain = new TextEvent(L"Gain " + to_wstring(targetTile->item->amount) + L" Gold", 25, ColorF::Yellow);
								goldGain->SetEvent(targetTile->m_Location, TextOption::DISAPPEAR, -0.4f, 120);
								m_TextEventS.push_back(goldGain);
							}
							else if (targetTile->item->origin == "resource_diamond") {
								TextEvent* goldGain = new TextEvent(L"Gain " + to_wstring(targetTile->item->amount) + L" Diamond !!", 25, ColorF::Yellow);
								goldGain->SetEvent(targetTile->m_Location, TextOption::DISAPPEAR, -0.4f, 120);
								UI::Get()->ShootDiamond(CAMERA->CorrecteLocation(&(p->GetCenter())));
								m_TextEventS.push_back(goldGain);
							}
							targetTile->item = nullptr;
						}
					}
				}

				return true;
			} 
		}

		return false;
	}

	vector<unique_ptr<Tile>>* GetTileVector() { return &m_Tiles; }

	unordered_map< ObjectType, vector<Object*>> mObjectMap;

	vector<Object*>mRender;
	vector<Object*>::iterator mObjectIter;
	vector<Object*>boomRender;
	
	vector<vector<float>> open_v;
	vector<vector<float>> close_v;
	vector<vector<int>> direction_v;

	vector<unique_ptr<Tile>> m_Tiles;
	vector<unique_ptr<Fog>> m_Fogs;
	Vector2 originFill;
	int startCount;

	Vector2 m_Render_Image_location;

	vector<Particle*> m_Particles;
	vector<TextEvent*> m_TextEventS;

	bool IsPlayerNearBy(Vector2 serach, int size);

	Vector2 GetPlayerCenter()
	{
		if (mObjectMap[PLAYER].size())
		{
			return mObjectMap[PLAYER][0]->GetCenter();
		}
		// 플레이어가 존재하지 않을 경우
		return Vector2(WINSIZE_X / 2, WINSIZE_Y / 2);
	}

	bool PlayerStay()
	{
		return mObjectMap[PLAYER].size() ? true : false;
	}

	int mOwnerCount;     // 현재 씬 플레이어의 수

	int mapsizex;
	int mapsizey;
};


#define OBJECT ObjectManager::Get()