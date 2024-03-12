#pragma once

enum TILE_TYPE
{
	TILE_TYPE_boss_floor_A,
	TILE_TYPE_floor_dirt1,
	TILE_TYPE_TEMP_floor_crystal,
	TILE_TYPE_TEMP_floor_water,
	TILE_TYPE_TEMP_floor_ice,
	TILE_TYPE_TEMP_floor_hotcoal,
	TILE_TYPE_zone3_floor,
	TILE_TYPE_zone3_floorB,
	TILE_TYPE_zone4_floor,
	TILE_TYPE_TEMP_shop_floor,
	end_of_tile_type
};

class Tile
{
public:
	TILE_TYPE tileType;
	Tile() = delete;
	~Tile() = default;

	Tile(Vector2 location, const string& imageName)
		: m_Location(location)           // 타일 실제 좌표
	{
		p = nullptr;
		item = nullptr;

		int dx = static_cast<int>(location.x / TILESIZE_X);
		int dy = static_cast<int>(location.y / TILESIZE_Y);
		tileType = TILE_TYPE_boss_floor_A;
		SetTileType(tileType);
		m_Image_Location = static_cast<int>(dx + dy) & 0x1 ? Vector2(0, 0) : Vector2(1, 0);
		fire = false;
		string torchs = "wall_torch";
		torch.Initialize("wall_torch", &(this->m_Location));
		torch.SetImageSize(Vector2(30, 60));
		torch.CalibratedImageLocation(Vector2(15, -40));
		this->SetImage(imageName);
		trap = TRAP_NONE;
		trapOn = false;
	} // 타일 기본 생성자

	Tile(TILE_TYPE type, Vector2 location)
		: m_Location(location)           // 타일 실제 좌표
	{
		p = nullptr;
		item = nullptr;

		SetTileType(type);

		int dx = static_cast<int>(location.x / TILESIZE_X);
		int dy = static_cast<int>(location.y / TILESIZE_Y);

		m_Image_Location = static_cast<int>(dx + dy) & 0x1 ? Vector2(0, 0) : Vector2(1, 0);
		fire = false;

		torch.Initialize("wall_torch", &(this->m_Location));
		torch.SetImageSize(Vector2(30, 60));
		torch.CalibratedImageLocation(Vector2(15, -40));
		trap = TRAP_NONE;
		trapOn = false;

	} // 타일 기본 생성자

	void SetTileType(TILE_TYPE type_)
	{
		tileType = type_;
		switch (type_)
		{
		case TILE_TYPE_boss_floor_A:
			SetImage("boss_floor_A");
			break;
		case TILE_TYPE_floor_dirt1:
			SetImage("floor_dirt1");
			break;
		case TILE_TYPE_TEMP_floor_crystal:
			SetImage("TEMP_floor_crystal");
			break;
		case TILE_TYPE_TEMP_floor_water:
			SetImage("TEMP_floor_water");
			break;
		case TILE_TYPE_TEMP_floor_ice:
			SetImage("TEMP_floor_ice");
			break;
		case TILE_TYPE_TEMP_floor_hotcoal:
			SetImage("TEMP_floor_hotcoal");
			break;
		case TILE_TYPE_zone3_floor:
			SetImage("zone3_floor");
			break;
		case TILE_TYPE_zone3_floorB:
			SetImage("zone3_floorB");
			break;
		case TILE_TYPE_zone4_floor:
			SetImage("zone4_floor");
			break;
		case TILE_TYPE_TEMP_shop_floor:
			SetImage("TEMP_shop_floor");
			break;
		}
	}


	// 타일 이미지 설정
	void SetImage(const string & ImageName)
	{
		m_Image = IMAGE->FindImage(ImageName);
	}

	// 타일 이미지 업데이트
	void Update(Vector2 image_location)
	{
		m_Image_Location.x = static_cast<int>(m_Image_Location.x);
		m_Image_Location.y = static_cast<int>(m_Image_Location.y);

		if (coinMulti > 1)
		{
			if (m_Image_Location.x == 0 && m_Image_Location.y == 0)
			{
				m_Image_Location.x = 0.f;
				m_Image_Location.y = 1.f;
			}
			else if (m_Image_Location.x == 0 && m_Image_Location.y == 1)
			{
				m_Image_Location.x = 0.f;
				m_Image_Location.y = 0.f;
			}
			if (m_Image_Location.x == 1 && m_Image_Location.y == 0)
			{
				m_Image_Location.x = 1.f;
				m_Image_Location.y = 1.f;
			}
			else if (m_Image_Location.x == 1 && m_Image_Location.y == 1)
			{
				m_Image_Location.x = 1.f;
				m_Image_Location.y = 0.f;
			}
		}
		else
		{
			this->m_Image_Location.x == 0.f ?
				m_Image_Location.x = 1.f : m_Image_Location.x = 0.f;
		}
	}

	void NonComboRenderInitailize()
	{
		int dx = static_cast<int>(m_Location.x / TILESIZE_X);
		int dy = static_cast<int>(m_Location.y / TILESIZE_Y);
		m_Image_Location = static_cast<int>(dx + dy) & 0x1 ? Vector2(0, 0) : Vector2(1, 0);
	}

	void ComboRenderInitailize()
	{
		int dx = static_cast<int>(m_Location.x / TILESIZE_X);
		int dy = static_cast<int>(m_Location.y / TILESIZE_Y);
		m_Image_Location = static_cast<int>(dx + dy) & 0x1 ? Vector2(0, 0) : Vector2(1, 1);
	}

	
	// 타일 이미지 렌더링
	void Render(Vector2 pos)
	{
		this->m_Image->FrameRender(m_Location, m_Image_Location, true);

		if (item != nullptr) {
			if (item->p->GetMaxFrameY() != 1)
			{
				item->p->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
				item->p->FrameRender(m_Location, pos, true);
			}
			else {
				item->p->SetSize(Vector2(37, 40));
				item->p->Render(m_Location + 15, true);
			}
		}

		if (trap != TRAP_NONE)
		{
			Vector2 trapRenderPos = { 0,0 };

			


			if (trapOn)
			{
				switch (trap)
				{
				case TRAP_UP:
					IMAGE->FindImage("bouncetrap")->Render(m_Location + 5,Vector2(0,0) ,true);
					break;
				case TRAP_LEFT:
					break;
				case TRAP_DOWN:
					break;
				}
			}
			else
			{
				switch (trap)
				{
				case TRAP_UP:
					break;
				case TRAP_LEFT:
					break;
				case TRAP_DOWN:
					break;
				}
			}
		}
		
	}

	void SetMinimapPing()
	{
		color = ColorF::White;
		if (this->p != nullptr)
		{
			if (p->type == WALL)
			{
				color = ColorF::Yellow;
			}
			else if (p->type == PLAYER)
			{
				color = ColorF::Blue;
			}
			else if (p->type == MONSTER)
			{
				color = ColorF::Red;
			}
			else
			{
				color = ColorF::White;
			}
		}
	}

	Vector2 m_Location;

	Image* m_Image;
	Trap trap;
	bool trapOn;
	Animation torch;
	bool fire;
	ColorF::Enum color;
	FloatRect rc;
	Vector2 m_Image_Location;
	Object* p;
	Item* item;
	bool m_IsEmpty;
};
