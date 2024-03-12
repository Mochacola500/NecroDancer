#include "stdafx.h"
#include "MapEditor.h"
#include <functional>

#define NOT(x) ! ((x))

void MapEditor::Init()
{
	page = 0;
	monsterIndex = 0;
	playerOne = true;

	ZeroVector2 = { 0,0 };
	Vector2 formSize(650.f, 400.f);
	Vector2 formPosition(250.f, 250.f);
	Vector2 commonButtonSize(90.f, 40.f);

	Upper_bar.Create(formPosition, Vector2(formSize.x, 40.f), "TEMP_overlay_black");
	Upper_bar.TextUp(L"네크로 크래프트 UI", 200, 2);
	form.Create(formPosition, formSize, "mincraft_Inventory");

	page_down.Create(Vector2(formPosition.x + 70.f, formPosition.y + 330.f), Vector2(40.f, 40.f), "ps4_L1");
	page_up.Create(Vector2(formPosition.x + 120.f, formPosition.y + 330.f), Vector2(40.f, 40.f), "ps4_R1");

	save_button.Create(Vector2(formPosition.x + 540.f, formPosition.y + 280.f), commonButtonSize, "ui");
	save_button.TextUp(L"저장하기", 5, 4);
	load_button.Create(Vector2(formPosition.x + 540.f, formPosition.y + 330.f), commonButtonSize, "ui");
	load_button.TextUp(L"불러오기", 5, 4);
	monster_button.Create(Vector2(formPosition.x + 240.f, formPosition.y + 280.f), commonButtonSize, "ui");
	monster_button.TextUp(L"몬스터", 8, 4);
	wall_button.Create(Vector2(formPosition.x + 240.f, formPosition.y + 330.f), commonButtonSize, "ui");
	wall_button.TextUp(L"벽돌", 14, 4);
	player_button.Create(Vector2(formPosition.x + 140.f, formPosition.y + 280.f), commonButtonSize, "ui");
	player_button.TextUp(L"플레이어", 5, 4);
	tile_button.Create(Vector2(formPosition.x + 340.f, formPosition.y + 280.f), commonButtonSize, "ui");
	tile_button.TextUp(L"타일", 14, 4);
	item_button.Create(Vector2(formPosition.x + 340.f, formPosition.y + 330.f), commonButtonSize, "ui");
	item_button.TextUp(L"아이템", 8, 4);
	misc_button.Create(Vector2(formPosition.x + 440.f, formPosition.y + 280.f), commonButtonSize, "ui");
	misc_button.TextUp(L"기타", 14, 4);
	erase_button.Create(Vector2(formPosition.x + 440.f, formPosition.y + 330.f), commonButtonSize, "ui");
	erase_button.TextUp(L"지우기", 8, 4);

	currentItem = nullptr;
	currentMonster = nullptr;
	currentWall = nullptr;
	currentTile = nullptr;
	currentMisc = nullptr;

	player = new Player(ZeroVector2);

	Upper_bar.AddChild(&form);
	Upper_bar.AddChild(&save_button);
	Upper_bar.AddChild(&load_button);
	Upper_bar.AddChild(&monster_button);
	Upper_bar.AddChild(&wall_button);
	Upper_bar.AddChild(&tile_button);
	Upper_bar.AddChild(&item_button);
	Upper_bar.AddChild(&misc_button);
	Upper_bar.AddChild(&player_button);
	Upper_bar.AddChild(&erase_button);
	Upper_bar.AddChild(&page_down);
	Upper_bar.AddChild(&page_up);

	CreateTypeChecker.OnCreate(CreateType_size);

	CreateSlotMake();
	CreateSlotMake();
	CreateSlotMake();

	for (int i = 0; i < ItemType::end_of_Do; ++i)
	{
		itemInfo.push_back(new Item(
			static_cast<ItemType>(i), 0, 1));
	}

	monsterInfo.push_back(new Slime(BLUE_SLIME, ZeroVector2));
	monsterInfo.push_back(new Slime(GREEN_SLIME, ZeroVector2));
	monsterInfo.push_back(new Slime(ORANGE_SLIME, ZeroVector2));

	monsterInfo.push_back(new Bat(BAT, ZeroVector2));
	monsterInfo.push_back(new Bat(BAT_BLACK, ZeroVector2));
	monsterInfo.push_back(new Bat(BAT_GREEN, ZeroVector2));
	monsterInfo.push_back(new Bat(BAT_RED, ZeroVector2));

	monsterInfo.push_back(new Elemental(FIRE_ELEMENTAL,ZeroVector2));
	monsterInfo.push_back(new Elemental(ICE_ELEMENTAL, ZeroVector2));

	monsterInfo.push_back(new Tresure(CHEST, ZeroVector2));
	monsterInfo.push_back(new Tresure(CHEST_BLACK, ZeroVector2));
	monsterInfo.push_back(new Tresure(CHEST_WHITE, ZeroVector2));

	monsterInfo.push_back(new Mimic(cauldron_coals_mimic, ZeroVector2));
	monsterInfo.push_back(new Mimic(cauldron_ice_mimic, ZeroVector2));

	Image* torch = IMAGE->FindImage("wall_torch");
	miscInfo.push_back(torch);


	for (int i = 0; i < WALL_TYPE::end_of_wall_type; ++i)
	{
		wallInfo.push_back(new Wall(static_cast<WALL_TYPE>(i), ZeroVector2));
	}

	for (int i = 0; i < TILE_TYPE::end_of_tile_type; ++i)
	{
		tileInfo.push_back(new Tile(static_cast<TILE_TYPE>(i), ZeroVector2));
	}
}

void MapEditor::Release()
{
	SAFE_DELETE(player);
	for (auto& deleted : buttons)
		SAFE_DELETE(deleted);
	buttons.clear();
	for (auto& deleted : itemInfo)
		SAFE_DELETE(deleted);
	itemInfo.clear();
	for (auto& deleted : monsterInfo)
		SAFE_DELETE(deleted);
	monsterInfo.clear();
	for (auto& deleted : wallInfo)
		SAFE_DELETE(deleted);
	wallInfo.clear();
	for (auto& deleted : tileInfo)
		SAFE_DELETE(deleted);
	tileInfo.clear();
}

void MapEditor::Update()
{
	if (Upper_bar.IsOnClick())
	{
		Upper_bar.SetSavePosition(_ptMouse);
	}

	if (Upper_bar.IsOnClickStay())
	{
		Upper_bar.Move(_ptMouse);
	}

	if (save_button.IsOnClick())
	{
		this->Save();
	}

	if (load_button.IsOnClick())
	{
		this->Load();
	}

	if (erase_button.IsOnClick())
	{
		OBJECT->Release();
		OBJECT->Init("","");
	}
	if (player_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_Player);
		page = 0;
	}
	if (monster_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_Monster);
		page = 0;
	}
	if (wall_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_wall);
		page = 0;
	}
	if (tile_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_tile);
		page = 0;
	}
	if (item_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_item);
		page = 0;
	}
	if (misc_button.IsOnClick())
	{
		CreateTypeChecker.OnCreate(CreateType_misc);
		page = 0;
	}
	if (page_up.IsOnClick())
	{
		if (page < 2)
		{
			page++;
		}
	}
	if (page_down.IsOnClick())
	{
		if (page > 0)
		{
			page--;
		}
	}

	if (KEY->IsStayKeyDown(VK_RBUTTON))
	{
		if (OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->item != nullptr)
		SAFE_DELETE(OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->item);
		OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->SetTileType(TILE_TYPE::TILE_TYPE_floor_dirt1);
		if(OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->p != nullptr)
		OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->p->SetAlive(false);
		OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->fire = false;
	}

	if (KEY->IsStayKeyDown(VK_LBUTTON))
	{
		for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
		{
			if (PtInRect(_ptMouse, FloatRect (
				buttons[i]->_form.left,
				buttons[i]->_form.top,
				buttons[i]->_form.right,
				buttons[i]->_form.bottom)))
			{
				switch (CreateTypeChecker.CreateTypeReturn())
				{
				case CreateType_Monster:
					if (i > monsterInfo.size() - 1) break;
					if (monsterInfo[i]->image.m_Image != nullptr)
					{
						currentMonster = monsterInfo[i];
						monsterIndex = i;
					}
					break;
				case CreateType_wall:
					if (i > wallInfo.size() - 1) break;
					if (wallInfo[i]->mImage != nullptr)
					{
						currentWall = wallInfo[i];
					}
					break;
				case CreateType_tile:
					if (i > tileInfo.size() - 1) break;
					if (tileInfo[i]->m_Image != nullptr)
					{
						currentTile = tileInfo[i];
					}
					break;
				case CreateType_item:
					if (i > itemInfo.size() - 1) break;
					if (itemInfo[i]->p != nullptr)
					{
						currentItem = itemInfo[i];
					}
					break;
				case CreateType_misc:
					if (i > miscInfo.size() - 1) break;
					if (miscInfo[i] != nullptr)
					{
						currentMisc = miscInfo[i];
					}
					break;
				}
			};
		}

		if ( NOT (PtInRect(_ptMouse, form._form)))
		{
			Object* temp_player = nullptr;
			Object* temp_monster = nullptr;
			Object* temp_wall = nullptr;
			switch (CreateTypeChecker.CreateTypeReturn())
			{
			case CreateType_Player:
				if (playerOne)
				{
					playerOne = false;
					player->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
					player->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
					temp_player = new Player(*player);
					OBJECT->AddObject(PLAYER, temp_player);
				}
				break;
			case CreateType_Monster:
				if (currentMonster != nullptr)
				{
					if (monsterIndex < 3)
					{
						temp_monster = new Slime((MONSTER_TYPE)monsterIndex, Vector2(0.f, 0.f));
						temp_monster->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
						temp_monster->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
						OBJECT->AddObject(MONSTER, temp_monster);
					}
					else if (monsterIndex < 7)
					{
						temp_monster = new Bat((MONSTER_TYPE)monsterIndex, Vector2(0.f, 0.f));
						temp_monster->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
						temp_monster->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
						OBJECT->AddObject(MONSTER, temp_monster);
					}
					else if (monsterIndex < 9)
					{
						temp_monster = new Elemental((MONSTER_TYPE)monsterIndex,Vector2(0.f, 0.f));
						temp_monster->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
						temp_monster->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
						OBJECT->AddObject(MONSTER, temp_monster);
					}
					else if (monsterIndex < 12)
					{
						temp_monster = new Tresure((MONSTER_TYPE)monsterIndex, Vector2(0.f, 0.f));
						temp_monster->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
						temp_monster->SetCenter(CAMERA->CorrecteMouse() * TILESIZE_X);
						OBJECT->AddObject(MONSTER, temp_monster);
					}
					else if (monsterIndex < 14)
					{
						temp_monster = new Mimic((MONSTER_TYPE)monsterIndex, Vector2(0.f, 0.f));
						temp_monster->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
						temp_monster->SetCenter(CAMERA->CorrecteMouse() * TILESIZE_X);
						OBJECT->AddObject(MONSTER, temp_monster);
					}
				}
				break;
			case CreateType_wall:
				if (currentWall->types != door_front)
				{
					temp_wall = new Wall(currentWall->types, ZeroVector2);
					temp_wall->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
					temp_wall->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
					OBJECT->AddObject(WALL, temp_wall);
				}
				else
				{
					temp_wall = new Door(currentWall->types, ZeroVector2);
					temp_wall->imageLocation = CAMERA->CorrecteMouse() * TILESIZE_X;
					temp_wall->SetCenter(CAMERA->CorrecteMouse()* TILESIZE_X);
					OBJECT->AddObject(WALL, temp_wall);
				}
				break;
			case CreateType_tile:
				OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->SetTileType(currentTile->tileType);
				break;
			case CreateType_item:
				OBJECT->GetTile(CAMERA->CorrecteMouse() * TILESIZE_X)->item = new Item(*currentItem);
				break;
			case CreateType_misc:
				OBJECT->GetTile(CAMERA->CorrecteMouse()* TILESIZE_X)->fire = true;
				break;
			}
		}
	}


}

void MapEditor::Save()
{
	ofstream tileMake("zone1_1_tile.txt");

	int tile_type = end_of_tile_type;
	int item_type = end_of_item_type;
	int fire = 0;
	vector<unique_ptr<Tile>>::iterator tile_iter;
	tile_iter = OBJECT->m_Tiles.begin();

	for (; tile_iter != OBJECT->m_Tiles.end(); ++tile_iter)
	{
		tile_type = (int)(*tile_iter)->tileType;

		(*tile_iter)->item != nullptr ?
			item_type = (int)(*tile_iter)->item->itemType
			:
			item_type = (int)ItemType::end_of_item_type;

		fire = (*tile_iter)->fire ? 1 : 0;

		tileMake << tile_type << " " << fire << " " << item_type << " ";

		tile_type = end_of_tile_type;
		item_type = end_of_item_type;
		fire = 0;
	}

	ofstream objectMake("zone1_1_object.txt");

	int monster_type = end_of_monster_type;
	int wall_type = end_of_wall_type;
	Vector2 object_location = {0,0};


	vector<Object*>object_iter = OBJECT->mRender;

	for (int i = 0; i < object_iter.size(); ++i)
	{
		monster_type = end_of_monster_type;
		wall_type = end_of_wall_type;
		object_location = { 0,0 };

		if (object_iter[i]->type == PLAYER)
		{
			monster_type = (int)player_monster_type;
			wall_type = (int)end_of_wall_type;
			object_location = object_iter[i]->GetCenter();
		}
		else if (object_iter[i]->type == WALL)
		{
			monster_type = (int)end_of_monster_type;
			wall_type = (int)dynamic_cast<Wall*>(object_iter[i])->types;
			object_location = object_iter[i]->GetCenter();
		}
		else if (object_iter[i]->type == MONSTER)
		{
			monster_type = (int)dynamic_cast<Monster*>(object_iter[i])->mosnterType;
			wall_type = (int)end_of_wall_type;
			object_location = object_iter[i]->GetCenter();
		}

		objectMake << monster_type << " " << wall_type << " " << object_location.x << " " << object_location.y << " ";
	}
}

void MapEditor::Load()
{
	ifstream tileMake("zone1_1_tile.txt");

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

	ifstream objectMake("zone1_1_object.txt");

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
			if (wall_type == door_front || wall_type == door_side)
			{
				OBJECT->AddObject(WALL, new Door(static_cast<WALL_TYPE>(wall_type),
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

void MapEditor::Render()
{
	form.TextUp(L"현재 페이지 " + to_wstring(this->page + 1) + L" / 3",
		490.f,  50.f, ColorF::Black, 15.f);
	form.Render();
	Upper_bar.Render();
	save_button.Render();
	load_button.Render();
	monster_button.Render();
	wall_button.Render();
	tile_button.Render();
	item_button.Render();
	player_button.Render();
	misc_button.Render();
	erase_button.Render();
	page_up.Render();
	page_down.Render();



	switch (CreateTypeChecker.CreateTypeReturn())
	{
		case CreateType_Monster:
			for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
			{
					if (i > monsterInfo.size() - 1) break;
					if (monsterInfo[i]->image.m_Image != nullptr)
					{
					monsterInfo[i]->image.m_Image->SetSize(Vector2(55.f, 55.f));
					monsterInfo[i]->image.m_Image->Render(
						Vector2(buttons[i]->_form.left, buttons[i]->_form.top),
						ZeroVector2);
				}
			}
			break;
		case CreateType_wall:
			for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
			{
					if (i > wallInfo.size() - 1) break;
					if (wallInfo[i]->mImage != nullptr)
					{
					wallInfo[i]->mImage->SetSize(Vector2(55.f, 55.f));
					wallInfo[i]->mImage->Render(
						Vector2(buttons[i]->_form.left, buttons[i]->_form.top),
						ZeroVector2);
				}
			}
			break;
		case CreateType_tile:
			for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
			{
				if (i > tileInfo.size() - 1) break;
				if (tileInfo[i]->m_Image != nullptr)
				{
					tileInfo[i]->m_Image->SetSize(Vector2(55.f, 55.f));
					tileInfo[i]->m_Image->Render(
						Vector2(buttons[i]->_form.left, buttons[i]->_form.top),
						ZeroVector2);
				}
			}
			break;
		case CreateType_item:
			for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
			{
				if (i > itemInfo.size() - 1) break;
				if (itemInfo[i]->p != nullptr)
				{
					itemInfo[i]->p->SetSize(Vector2(55.f, 55.f));
					itemInfo[i]->p->Render(
						Vector2(buttons[i]->_form.left, buttons[i]->_form.top),
						ZeroVector2);
				}
			}
			break;
		case CreateType_misc:
			for (int i = page * MAPTOOL_PAGE_MAX; i < (page + 1) * MAPTOOL_PAGE_MAX; ++i)
			{
				if (i > miscInfo.size() - 1) break;
				if (miscInfo[i] != nullptr)
				{
					miscInfo[i]->SetSize(Vector2(55.f, 55.f));
					miscInfo[i]->Render(
						Vector2(buttons[i]->_form.left, buttons[i]->_form.top),
						ZeroVector2);
				}
			}
			break;
	}

	switch (CreateTypeChecker.CreateTypeReturn())
	{
	case CreateType_Monster:
		if (currentMonster != nullptr)
		{
			currentMonster->image.m_Image->SetAlpha(0.5f);
			currentMonster->image.m_Image->SetSize(Vector2(55.f, 55.f));
			currentMonster->image.m_Image->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
		}
		break;
	case CreateType_wall:
		if (currentWall != nullptr)
		{
			currentWall->mImage->SetAlpha(0.5f);
			currentWall->mImage->SetSize(Vector2(55.f, 55.f));
			currentWall->mImage->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
		}
		break;
	case CreateType_tile:
		if (currentTile != nullptr)
		{
			currentTile->m_Image->SetAlpha(0.5f);
			currentTile->m_Image->SetSize(Vector2(55.f, 55.f));
			currentTile->m_Image->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
		}
		break;
	case CreateType_item:
		if (currentItem != nullptr)
		{
			currentItem->p->SetAlpha(0.5f);
			currentItem->p->SetSize(Vector2(55.f, 55.f));
			currentItem->p->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
		}
		break;
	case CreateType_misc:

		break;
	case CreateType_Player:
		if (player != nullptr)
		{
			player->torso.m_Image->SetAlpha(0.5f);
			player->head.m_Image->SetAlpha(0.5f);
			player->torso.m_Image->SetSize(Vector2(55.f, 55.f));
			player->head.m_Image->SetSize(Vector2(55.f, 55.f));
			player->torso.m_Image->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
			player->head.m_Image->Render(
				Vector2(_ptMouse.x + 10.f, _ptMouse.y + 5.f),
				ZeroVector2);
		}
		break;
	}
}


void MapEditor::CreateSlotMake()
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			Transform* asdf = new Transform(Vector2(250 + 25.f + x * 60.f, 250 + 80.f + y * 60.f), Vector2(55.f, 55.f));
			buttons.push_back(asdf);
			Upper_bar._childs.push_back(asdf);
		}
	}
}

void MapEditor::NullCurrent()
{
	currentMonster = nullptr;
	currentItem = nullptr;
	currentWall = nullptr;
	currentTile = nullptr;
}
