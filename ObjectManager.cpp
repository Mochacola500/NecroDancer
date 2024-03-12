#include "stdafx.h"
#include "ObjectManager.h"

ColorF::Enum ColorRare(int q)
{
	switch (q)
	{
	case 0:
		return ColorF::White;
	case 1:
		return ColorF::Blue;
	case 2:
		return ColorF::Pink;
	case 3:
		return ColorF::Orange;
	}
	return ColorF::White;
}

bool inGame = true;

int _ComboStack = 0;


inline int CalculateDirection(int dir)
{
	if (dir == 0) return 2;
	if (dir == 1) return 3;
	if (dir == 2) return 0;
	if (dir == 3) return 1;
}

typedef struct Path
{
	float fCost;
	float gCost;
	int x;
	int y;

	Path(int x, int y, float gCost, float fCost)
		: x(x)
		, y(y)
		, fCost(fCost)
		, gCost(gCost)
	{}

	void CalculateCost(int endx, int endy)
	{
		fCost = gCost + CalculateHeuristics(endx, endy);
	}

	inline void CalculateG_Cost(const int& directuin)
	{// 8 방향일경우 대각선인지 아닌지 검사해 14,10 8방향이 아닐경우 10값
		gCost = (direction == 8 ? (directuin % 2 == 0 ? 10 : 14) : 10);
	}

	inline float CalculateHeuristics(const int& endx, const int& endy)
	{
		return GetDistance(Vector2(x, y), Vector2(endx, endy));
	}

};

inline bool operator< (const Path& node1, const Path& node2)
{
	return node1.fCost > node2.fCost;
}

inline bool IsDestination(int x, int y, int endx, int endy)
{
	if (x == endx && y == endy) {
		return true;
	}
	return false;
}

void ObjectManager::Init(string filename, string filename2)
{

	for (int i = 0; i < ObjectType::OBJECT_TYPE_END; ++i)
	{
		mObjectMap.insert(make_pair((ObjectType)i, vector<Object*>()));
	}

	this->m_Render_Image_location = { 0.f , 0.f };

	Vector2 location = { 0.f,0.f };
	Vector2 image_location = { 0.f,0.f };

	float bit = 1.f;

	mapsizex = 40;
	mapsizey = 40;

	open_v.clear();
	close_v.clear();
	direction_v.clear();

	for (int y = 0; y < mapsizex; ++y) {

		open_v.push_back(vector<float>());
		close_v.push_back(vector<float>());
		direction_v.push_back(vector<int>());

		for (int x = 0; x < mapsizey; ++x) {
			location = { x * (TILESIZE_X), y * (TILESIZE_Y) };
			image_location = { bit, 0.f };
			m_Tiles.push_back(make_unique<Tile>(location, "boss_floor_A"));
			m_Fogs.push_back(make_unique<Fog>(location));

			open_v[y].push_back(0);
			close_v[y].push_back(0);
			direction_v[y].push_back(0);
		}
	}

	for (const auto& renderTarget : m_Fogs) {
		renderTarget.get()->check = true;
	}
	if (filename != "")
	{
		ifstream tileMake(filename);

		int tile_type = end_of_tile_type;
		int item_type = end_of_item_type;
		int fire = 0;
		int index = 0;

		while (tileMake >> tile_type >> fire >> item_type)
		{
			if (tile_type != end_of_tile_type)
			{
				OBJECT->m_Tiles[index].get()->SetTileType(static_cast<TILE_TYPE>(tile_type));
				OBJECT->m_Tiles[index].get()->fire = fire;
			}
			if (item_type != end_of_item_type)
				OBJECT->m_Tiles[index].get()->item = new Item(static_cast<ItemType>(item_type));

			index++;
		}

		ifstream objectMake(filename2);

		int monster_type = end_of_monster_type;
		int wall_type = end_of_wall_type;
		Vector2 object_location = { 0,0 };

		while (objectMake >> monster_type >> wall_type >> object_location.x >> object_location.y)
		{
			if (monster_type == player_monster_type)
			{
				OBJECT->AddObject(PLAYER, new Player(Vector2(object_location.x, object_location.y)));
			}
			else if (monster_type != end_of_monster_type)
			{
				if (monster_type < 3)
				{
					Object* temp_monster = new Slime((MONSTER_TYPE)monster_type, Vector2(0.f, 0.f));
					temp_monster->imageLocation = Vector2(object_location.x, object_location.y);
					temp_monster->SetCenter(Vector2(object_location.x, object_location.y));
					OBJECT->AddObject(MONSTER, temp_monster);
				}
				else if (monster_type < 7)
				{
					Object* temp_monster = new Bat((MONSTER_TYPE)monster_type, Vector2(0.f, 0.f));
					temp_monster->imageLocation = Vector2(object_location.x, object_location.y);
					temp_monster->SetCenter(Vector2(object_location.x, object_location.y));
					OBJECT->AddObject(MONSTER, temp_monster);
				}
				else if (monster_type < 9)
				{
					Object* temp_monster = new Elemental((MONSTER_TYPE)monster_type, Vector2(0.f, 0.f));
					temp_monster->imageLocation = Vector2(object_location.x, object_location.y);
					temp_monster->SetCenter(Vector2(object_location.x, object_location.y));
					OBJECT->AddObject(MONSTER, temp_monster);
				}
				else if (monster_type < 12)
				{
					Object* temp_monster = new Tresure((MONSTER_TYPE)monster_type, Vector2(0.f, 0.f));
					temp_monster->imageLocation = Vector2(object_location.x, object_location.y);
					temp_monster->SetCenter(Vector2(object_location.x, object_location.y));
					OBJECT->AddObject(MONSTER, temp_monster);
				}
				else if (monster_type < 14)
				{
					Object* temp_monster = new Mimic((MONSTER_TYPE)monster_type, Vector2(0.f, 0.f));
					temp_monster->imageLocation = Vector2(object_location.x, object_location.y);
					temp_monster->SetCenter(Vector2(object_location.x, object_location.y));
					OBJECT->AddObject(MONSTER, temp_monster);
				}
			}
			else if (wall_type != end_of_wall_type)
			{
				if (wall_type == door_front)
				{
					OBJECT->AddObject(WALL, new Door(door_front,
						Vector2(object_location.x, object_location.y)));
				}
				else
				{
					OBJECT->AddObject(WALL, new Wall(static_cast<WALL_TYPE>(wall_type),
						Vector2(object_location.x, object_location.y)));
				}
			}
		}
	}

}

void ObjectManager::Update()
{
	for (int i = 0; i < ObjectType::OBJECT_TYPE_END; ++i) {
		for (int j = 0; j < mObjectMap[(ObjectType)i].size(); ++j) {
			if (mObjectMap[(ObjectType)i][j]->GetAlive()) {
				mObjectMap[(ObjectType)i][j]->Update();
			}
			else {
				mObjectMap[(ObjectType)i].erase(mObjectMap[(ObjectType)i].begin() + j);
				j--;
			}
		}
	}
}

inline bool Z_Order(Object * p, Object * p2)
{
	return p->GetCenter().y < p2->GetCenter().y;
}


void ObjectManager::Render()
{
	if (KEY->IsOnceKeyDown(VK_RIGHT))
	{
		SCENE->ChangeScene("Test");
		return;
	}
	if (KEY->IsOnceKeyDown(VK_LEFT))
	{
		SCENE->ChangeScene("Zone1");
		return;
	}

	Vector2 camera = CAMERA->GetCameraLocation();
	camera /= TILESIZE_X;

	int startX = static_cast<int>(camera.x) - 1;
	if (startX < 0)
	{
		startX = 0;
	}
	int startY = static_cast<int>(camera.y) - 1;
	if (startY < 0)
	{
		startY = 0;
	}
	int endX = static_cast<int>((camera.x + 23)) + 1;
	if (endX > mapsizex - 1)
	{
		endX = mapsizex - 1;
	}
	int endY = static_cast<int>((camera.y + 23)) + 1;
	if (endY > mapsizey - 1)
	{
		endY = mapsizey - 1;
	}

	int overy = 0;
	for (int i = startY * mapsizey + startX; i < endY * mapsizey + endX; ++i) {

		m_Tiles[i].get()->m_Image->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
		m_Tiles[i].get()->SetMinimapPing();
		if (OnFog(m_Tiles[i].get()->m_Location)) {
			m_Tiles[i].get()->Render(Vector2(0, 1));
		}
		else {
			m_Tiles[i].get()->Render(Vector2(0, 0));
		}
		overy++;
		if (overy > 24)
		{
			i += mapsizey - 25;
			overy = 0;
		}
	}

	if (!inGame)
	{
		for (int i = 0; i < ObjectType::OBJECT_TYPE_END; ++i) {
			for (int j = 0; j < mObjectMap[(ObjectType)i].size(); ++j) {
				if (mObjectMap[(ObjectType)i][j]->GetAlive()) {
				}
				else {
					mObjectMap[(ObjectType)i].erase(mObjectMap[(ObjectType)i].begin() + j);
					j--;
				}
			}
		}
	}

	sort(mRender.begin(), mRender.end(), Z_Order);

	for (int i = 0; i < mRender.size(); ++i)
	{
		if (mRender[i]->GetAlive())
		{
			mRender[i]->Render();
		}
		else {
			this->GetTile(mRender[i])->p = nullptr; // 원래 밟은자리 널로변경
			mRender[i]->DeadEvent(); // 사망이벤트 실행

			SAFE_DELETE(mRender[i]);
			mRender.erase(mRender.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < boomRender.size(); ++i)
	{
		if (boomRender[i]->GetAlive())
		{
			boomRender[i]->Update();
			boomRender[i]->Render();
		}
		else {
			SAFE_DELETE(boomRender[i]);
			boomRender.erase(boomRender.begin() + i);
			i--;
		}
	}

	overy = 0;

	for (int i = startY * mapsizey + startX; i < endY * mapsizey + endX; ++i) {
		if (m_Tiles[i].get()->fire)
		{
			if (m_Tiles[i].get()->torch.CheckLastImage())
			{
				m_Tiles[i].get()->torch.SetImageFlipTable();
			}
			m_Tiles[i].get()->torch.Render();
		}
		overy++;
		if (overy > 24)
		{
			i += mapsizey - 25;
			overy = 0;
		}
	}

	if (!inGame)
	{
		overy = 0;
		for (int i = startY * mapsizey + startX; i < endY * mapsizey + endX; ++i)
		{
			if (!m_Fogs[i].get()->isOnceOpen == true)
			{
				Vector2 location = m_Tiles[i].get()->m_Location;

				int minx = static_cast<int>(CAMERA->CorrecteLocation(&location).x / TILESIZE_X * 4.f);
				int miny = static_cast<int>(CAMERA->CorrecteLocation(&location).y / TILESIZE_Y * 4.f);

				FloatRect rc =
				{
				1200.f + minx,
				600.f + miny,
				1204.f + minx,
				604.f + miny
				};

				if (rc.left > 999)
					D2DRENDER->FillRectangle(rc, m_Tiles[i].get()->color, 0.8f);
			}

			overy++;
			if (overy > 24)
			{
				i += mapsizey - 25;
				overy = 0;
			}
		}
	}


	if (inGame)
	{

		for (int i = 0; i < m_Particles.size(); ++i) {
			if (m_Particles[i]->EndImage() != false) {
				m_Particles[i]->Render();
			}
			else
			{
				m_Particles.erase(m_Particles.begin() + i);
				i--;
			}
		}

		for (const auto& renderTarget : m_Fogs) {
			renderTarget.get()->Render();
		}

		for (int i = 0; i < m_TextEventS.size(); ++i) {
			if (m_TextEventS[i]->life != false) {
				m_TextEventS[i]->Render();
			}
			else
			{
				m_TextEventS.erase(m_TextEventS.begin() + i);
				i--;
			}
		}

		if (mObjectMap[PLAYER].size())
		{
			Player* p = dynamic_cast<Player*>(mObjectMap[PLAYER][0]);

			Vector2 position;

			for (int inde = 0; inde < 4; ++inde) {
				position = Vector2(
					p->GetCenter().x + dx[inde] * TILESIZE_X,
					(p->GetCenter().y + 16.f) + dy[inde] * TILESIZE_Y);

				if ((IsInIndex(position.x / TILESIZE_X, position.y / TILESIZE_Y)))
				{
					continue;
				}
				if (GetTile(position)->item != nullptr)
				{
					IDWriteTextLayout* t;
					Item* nameP = GetTile(position)->item;
					D2DRENDER->LayOutMake(&t,
						nameP->ItemName,
						15.f);
					position = this->GetTileIndex(position) * TILESIZE_X;
					position.x -= nameP->ItemName.length() * 2.f;
					position.y -= 8;
					position = CAMERA->CorrecteLocation(&position);

					D2DRENDER->FillRectangle(FloatRect(position.x, position.y,
						position.x + nameP->ItemName.length() * 8.f, position.y + 20.f),
						ColorF::Black, 0.7f);
					D2DRENDER->RenderText(position, t, ColorRare(nameP->qulity));
					t->Release();
				}

			}

		}

		for (int i = startY * mapsizey + startX; i < endY * mapsizey + endX; ++i)
		{
			if (m_Fogs[i].get()->isOnceOpen)
			{
				Vector2 location = m_Tiles[i].get()->m_Location;

				int minx = static_cast<int>(CAMERA->CorrecteLocation(&location).x / TILESIZE_X * 4.f);
				int miny = static_cast<int>(CAMERA->CorrecteLocation(&location).y / TILESIZE_Y * 4.f);

				FloatRect rc =
				{
				1200.f + minx,
				600.f + miny,
				1204.f + minx,
				604.f + miny
				};

				if (rc.left > 999)
					D2DRENDER->FillRectangle(rc, m_Tiles[i].get()->color, 0.8f);
			}

			overy++;
			if (overy > 23)
			{
				i += mapsizey - 24;
				overy = 0;
			}
		}
	}
}

void ObjectManager::Release()
{
	for (auto& Owners : mObjectMap)
	{
		mObjectIter = Owners.second.begin();
		for (; mObjectIter != Owners.second.end();)
		{
			//SAFE_RELEASE((*mObjectIter));
			SAFE_DELETE((*mObjectIter));
			mObjectIter++;
		}
		Owners.second.clear();
	}

	mObjectMap.clear();
	mRender.clear();

	for (int i = 0; i < m_Tiles.size(); ++i) {
		m_Tiles[i].release();
	}
	m_Tiles.clear();

	for (int i = 0; i < m_Fogs.size(); ++i) {
		m_Fogs[i].release();
	}
	m_Fogs.clear();

	for (int i = 0; i < m_Particles.size(); ++i) {
		SAFE_DELETE(m_Particles[i]);
	}
	m_Particles.clear();

	for (int i = 0; i < m_TextEventS.size(); ++i) {
		SAFE_DELETE(m_TextEventS[i]);
	}
	m_TextEventS.clear();
}

void ObjectManager::TileUpdate()
{
	for (const auto& updateTarget : m_Tiles)
		updateTarget.get()->Update(m_Render_Image_location);
}

void ObjectManager::TileNonComboUpdate()
{
	for (const auto& updateTarget : m_Tiles) {
		updateTarget.get()->NonComboRenderInitailize();
	}
}

void ObjectManager::TileComboUpdate()
{
	for (const auto& updateTarget : m_Tiles) {
		updateTarget.get()->ComboRenderInitailize();
	}
}

void ObjectManager::MonsterUpdate()
{
	if (mObjectMap[PLAYER].size()) mObjectMap[PLAYER][0]->BeatUpdate();
	for (const auto& updateTarget : mObjectMap[MONSTER])
		updateTarget->BeatUpdate();
	for (const auto& updateTarget : boomRender)
		updateTarget->BeatUpdate();
}

bool ObjectManager::IsPlayerNearBy(Vector2 search, int size)
{
	Vector2 find = this->GetTileIndex(search);
	Vector2 target = this->GetTileIndex(this->GetPlayerCenter());

	for (int i = find.x - size / 2; i < find.x + size / 2; ++i)
	{
		for (int j = find.y - size / 2; j < find.y + size / 2; ++j)
		{
			if (!IsInIndex(i, j))
			{
				if (IsDestination(i, j, target.x, target.y))
				{
					return true;
				}
			}
		}
	}
	return false;
}

inline bool ObjectManager::IsInIndex(int x, int y)
{
	if (x >= 0 && y >= 0 && x < mapsizex && y < mapsizey) {
		return false;
	}
	return true;
}



Vector2 ObjectManager::PathFinder(Vector2 start, Vector2 end)
{
	// 탐색 노드
	priority_queue<Path> openNode[2];

	// 현재 인덱스
	static int currentIndex = 0;
	Path* startNode;
	Path* childNode;
	static int currentDirection;
	static int x, y, xdx, ydy;  //좌표

	// 열린 노드와 닫힌 노드 초기화
	for (y = 0; y < mapsizey; ++y)
	{
		for (x = 0; x < mapsizex; ++x)
		{
			open_v[x][y] = 0;
			if (m_Tiles[y * mapsizey + x].get()->p == nullptr)
			{
				close_v[x][y] = 0;
			}
			else
			{
				if (m_Tiles[y * mapsizey + x].get()->p->type == WALL)
				{
					close_v[x][y] = 1;
				}
				else
				{
					close_v[x][y] = 0;
				}
			}
		}
	}

	// 시작 인덱스와 끝 인덱스 설정
	Vector2 startIndex = GetTileIndex(start);
	Vector2 endIndex = GetTileIndex(end);

	// 닫힌 노드 중 자기자신과 도달 위치를 0으로 다시만들어준다.
	close_v[startIndex.x][startIndex.y] = 0;
	close_v[endIndex.x][endIndex.y] = 0;

	// 시작 노드를 설정
	startNode = new Path(startIndex.x, startIndex.y, 0, 0);
	startNode->CalculateCost(endIndex.x, endIndex.y);
	openNode[currentIndex].push(*startNode);

	x = startIndex.x;
	y = startIndex.y;

	// 열린노드의 이동 값을 시작노드의 이동값으로 설정
	open_v[x][y] = startNode->fCost;

	// 더 이상 탐색할 곳이 없을 때 탈출
	while (!(openNode[currentIndex].empty()))
	{
		// 새로운 검색할 노드 설정
		startNode = new Path(openNode[currentIndex].top().x, openNode[currentIndex].top().y,
			openNode[currentIndex].top().gCost, openNode[currentIndex].top().fCost);

		x = startNode->x;
		y = startNode->y;

		// 검색할 노드를 사용했으니 제거
		openNode[currentIndex].pop();

		// 값 초기화
		open_v[x][y] = 0;
		// 검색했으니 다시 검색하지 못하도록 표시
		close_v[x][y] = 1;

		// 도착했다면
		if (IsDestination(x, y, endIndex.x, endIndex.y))
		{
			// 반환할 벡터
			vector<Vector2> followList;
			Vector2 goal;

			// 출발 지점이 될때 까지
			while (!IsDestination(x, y, startIndex.x, startIndex.y))
			{
				currentDirection = direction_v[x][y]; // 다음 노드 방향 설정
				goal =
				{
					x * TILESIZE_X,
					y * TILESIZE_Y
				};

				followList.push_back(Vector2(goal));
				x += dx[currentDirection]; // 다음 방향 x 좌표를 변경해준다.
				y += dy[currentDirection]; // 다음 방향 y좌표를 변경해준다.
			}

			SAFE_DELETE(startNode);
			if (followList.size() > 0)
			{
				return followList[followList.size() - 1];
			}
			else
			{
				return Vector2(-1, -1);
			}

			//while (!openNode[currentIndex].empty()) openNode[currentIndex].pop();
			//return followList;
		}

		for (int i = 0; i < direction; ++i)
		{
			xdx = x + dx[i];
			ydy = y + dy[i];

			// 인덱스 안에 있으면서 닫혀있지 않은(검사하지 않은) 노드여야한다.
			if (!(IsInIndex(xdx, ydy)))
			{
				if (close_v[xdx][ydy] == 0)
				{
					childNode = new Path(xdx, ydy, startNode->gCost, startNode->fCost);
					childNode->CalculateG_Cost(i); // g값을 구해준다. for문의 i 를 통해 배열에 인덱스에 접근해 가져온 값을 통해 방향을 알아낸다.
					childNode->CalculateCost(endIndex.x, endIndex.y); // g값을 토대로 목표까지 거리를 구해 최종비용을 구한다.

					// 오픈노드에 이미 담겨있는 노드가 아니라면
					if (open_v[xdx][ydy] == 0)
					{// 이동 비용값을 담아준다.
						open_v[xdx][ydy] = childNode->fCost;
						direction_v[xdx][ydy] = CalculateDirection(i);
						openNode[currentIndex].push(*childNode);
					} // 오픈 노드에 담겨있는데 비용이 더 작은(가까운) 노드라면
					else if (open_v[xdx][ydy] > childNode->fCost)
					{
						// 노드를 변경해준다.
						open_v[xdx][ydy] = childNode->fCost;
						direction_v[xdx][ydy] = CalculateDirection(i);
						// 오픈노드에 새로운 노드에 넣어준다.
						while (!(openNode[currentIndex].top().x == xdx &&
							openNode[currentIndex].top().y == ydy))
						{
							openNode[1 - currentIndex].push(openNode[currentIndex].top());
							openNode[currentIndex].pop();
						}
						openNode[currentIndex].pop();

						if ((openNode[currentIndex].size() > openNode[1 - currentIndex].size()))
						{
							currentIndex = 1 - currentIndex;
						}
						while (!openNode[currentIndex].empty())
						{
							openNode[1 - currentIndex].push(openNode[currentIndex].top());
							openNode[currentIndex].pop();
						}
						// 더 좋은 노드를 삽입한다.
						currentIndex = 1 - currentIndex;
						openNode[currentIndex].push(*childNode);
					}
					else
					{
						SAFE_DELETE(childNode);
					}
				}
			}
		}
		SAFE_DELETE(startNode);
	}
	return Vector2(-1, -1);
}


// 콤보 상태가 바뀔 때, 함수 1회 실행
void ObjectManager::ComboRenderImageLocation()
{
	m_Render_Image_location.y ?
		m_Render_Image_location.y = 0.f : m_Render_Image_location.y = 1.f;
}

// 비트가 추가될 때 마다 1회 실행
void ObjectManager::BinaryImageLocation()
{
	m_Render_Image_location.x ?
		m_Render_Image_location.x = 0.f : m_Render_Image_location.x = 1.f;
}


void ObjectManager::Fill(Object * pos, int count)
{
	int x = 0;
	int y = 0;

	Vector2 camera = CAMERA->GetCameraLocation();
	camera /= TILESIZE_X;

	int startX = static_cast<int>(camera.x) - 1;
	if (startX < 0)
	{
		startX = 0;
	}
	int startY = static_cast<int>(camera.y) - 1;
	if (startY < 0)
	{
		startY = 0;
	}
	int endX = static_cast<int>((camera.x + 23)) + 1;
	if (endX > mapsizex - 1)
	{
		endX = mapsizex - 1;
	}
	int endY = static_cast<int>((camera.y + 23)) + 1;
	if (endY > mapsizey - 1)
	{
		endY = mapsizey - 1;
	}

	int overy = 0;
	if (pos != nullptr) 
	{
		for (int i = startY * mapsizey + startX; i < endY * mapsizey + endX; ++i)
		{
			m_Fogs[i].get()->check = false;

			if (m_Fogs[i].get()->isOnceOpen == true)
			{
				m_Fogs[i].get()->light = 0.8f;
			}
			else
			{
				m_Fogs[i].get()->light = 1.0f;
			}
			overy++;
			if (overy > 23)
			{
				i += mapsizey - 24;
				overy = 0;
			}
		}
	}
	else // 안개입힐 대상 객체가 존재하지 않음.
	{
		for (const auto& renderTarget : m_Fogs) {
			renderTarget.get()->check = false;
			renderTarget.get()->light = 0.0f;
		}
	}

	x = static_cast<int>((pos->GetCenter().x + 16.f) / TILESIZE_X);
	y = static_cast<int>((pos->GetCenter().y + 16.f) / TILESIZE_X);

	originFill = Vector2(x, y);
	startCount = count;
	FillFog(originFill, count);
}

void ObjectManager::FillFog(Vector2 pos, int count)
{
	float lightFower = GetDistance(originFill, pos) / (startCount + 1);

	if (count > 0)
	{
		if (pos.x > -1 && pos.y > -1 &&
			pos.x < mapsizex && pos.y < mapsizey)
		{
			Fog* fog = m_Fogs[(pos.y * mapsizey) + pos.x].get();

			if (fog->check) return;

				if (m_Tiles[(pos.y * mapsizey) + pos.x].get()->p != nullptr)
				{
					if (m_Tiles[(pos.y * mapsizey) + pos.x].get()->p->type == WALL)
					{
						fog->light = static_cast<float>(lightFower);
						fog->isOnceOpen = true;
						fog->check = true;
						count = 1;
						if (m_Tiles[(pos.y * mapsizey) + pos.x].get()->fire == true)
						{
							FillFog(Vector2(pos.x + 1, pos.y), count + 3);
							FillFog(Vector2(pos.x - 1, pos.y), count + 3);
							FillFog(Vector2(pos.x, pos.y + 1), count + 3);
							FillFog(Vector2(pos.x, pos.y - 1), count + 3);
						}
						else
						{
							FillFog(Vector2(pos.x + 1, pos.y), count - 1);
							FillFog(Vector2(pos.x - 1, pos.y), count - 1);
							FillFog(Vector2(pos.x, pos.y + 1), count - 1);
							FillFog(Vector2(pos.x, pos.y - 1), count - 1);
						}
					}
					else
					{
						fog->light = static_cast<float>(lightFower);
						fog->isOnceOpen = true;
						fog->check = true;

						FillFog(Vector2(pos.x + 1, pos.y), count - 1);
						FillFog(Vector2(pos.x - 1, pos.y), count - 1);
						FillFog(Vector2(pos.x, pos.y + 1), count - 1);
						FillFog(Vector2(pos.x, pos.y - 1), count - 1);
					}
				}
				else
				{
					fog->light = static_cast<float>(lightFower);
					fog->isOnceOpen = true;
					fog->check = true;

					FillFog(Vector2(pos.x + 1, pos.y), count - 1);
					FillFog(Vector2(pos.x - 1, pos.y), count - 1);
					FillFog(Vector2(pos.x, pos.y + 1), count - 1);
					FillFog(Vector2(pos.x, pos.y - 1), count - 1);
				}
			
		}
	}
}
