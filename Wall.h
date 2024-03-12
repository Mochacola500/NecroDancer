#pragma once
#include "Object.h"
class Wall 
	: public Object
{
public:
	WALL_TYPE types;

	Wall();
	~Wall();

	//실제 사용 생성자
	Wall(WALL_TYPE type, Vector2 location)
	{
		this->mCenter = location;
		this->type = WALL;
		this->types = type;
		////////////////
		switch (types)
		{
		case zone1_catacomb_cracked:
			this->mImage = IMAGE->FindImage("zone1_catacomb_cracked");
			this->hp = 10;
			break;
		case zone1_wall_dirt_cracked:
			this->mImage = IMAGE->FindImage("zone1_wall_dirt_cracked");
			this->hp = 1;
			break;
		case zone1_wall_stone_cracked:
			this->mImage = IMAGE->FindImage("zone1_wall_stone_cracked");
			this->hp = 2;
			break;
		case zone2_wall_stone:
			this->mImage = IMAGE->FindImage("zone2_wall_stone");
			this->hp = 2;
			break;
		case zone2_wall_dirt_crack:
			this->mImage = IMAGE->FindImage("zone2_wall_dirt_crack");
			this->hp = 1;
			break;
		case zone2_wall_stone_crack:
			this->mImage = IMAGE->FindImage("zone2_wall_stone_crack");
			this->hp = 2;
			break;
		case wall_shop_crypt:
			this->mImage = IMAGE->FindImage("wall_shop_crypt");
			this->hp = 10;
			break;
		case wall_shop_crypt_dark_cracked:
			this->mImage = IMAGE->FindImage("wall_shop_crypt_dark_cracked");
			this->hp = 10;
			break;
		case wall_stone_crypt:
			this->mImage = IMAGE->FindImage("wall_stone_crypt");
			this->hp = 2;
			break;
		case end_of_world:
			this->mImage = IMAGE->FindImage("end_of_world");
			this->hp = 10;
			break;
		case zone3_wall_stone_cold:
			this->mImage = IMAGE->FindImage("zone3_wall_stone_cold");
			this->hp = 2;
			break;
		case zone3_wall_stone_hot:
			this->mImage = IMAGE->FindImage("zone3_wall_stone_hot");
			this->hp = 2;
			break;
		case zone4_wall_catacomb_A:
			this->mImage = IMAGE->FindImage("zone4_wall_catacomb_A");
			this->hp = 1;
			break;
		case zone4_wall_rock_A:
			this->mImage = IMAGE->FindImage("zone4_wall_rock_A");
			this->hp = 2;
			break;
		case wall_dirt_crypt_diamond1:
			this->mImage = IMAGE->FindImage("wall_dirt_crypt_diamond1");
			this->hp = 1;
			break;
		case wall_dirt_zone2_diamond1:
			this->mImage = IMAGE->FindImage("wall_dirt_zone2_diamond1");
			this->hp = 1;
			break;
		case wall_dirt_zone3cold_diamond1:
			this->mImage = IMAGE->FindImage("wall_dirt_zone3cold_diamond1");
			this->hp = 1;
			break;
		case wall_dirt_zone3HOT_diamond1:
			this->mImage = IMAGE->FindImage("wall_dirt_zone3HOT_diamond1");
			this->hp = 1;
			break;
		case wall_dirt_zone4_diamond1:
			this->mImage = IMAGE->FindImage("wall_dirt_zone4_diamond1");
			this->hp = 1;
			break;
		case necrodancer_wall:
			this->mImage = IMAGE->FindImage("necrodancer_wall");
			this->hp = 1;
			break; 
		case boss_wall:
			this->mImage = IMAGE->FindImage("boss_wall");
			this->hp = 10;
			break; 
		case door_front:
			this->mImage = IMAGE->FindImage("door_front");
			this->hp = 1;
			break;
		case door_side:
			this->mImage = IMAGE->FindImage("door_side");
			this->hp = 1;
			break;
		case wall_catacomb_crypt1:
			this->mImage = IMAGE->FindImage("wall_catacomb_crypt1");
			this->hp = 2;
			break;
		case wall_catacomb_crypt2:
			this->mImage = IMAGE->FindImage("wall_catacomb_crypt2");
			this->hp = 2;
			break;
		case cauldron_coals:
			this->mImage = IMAGE->FindImage("cauldron_coals");
			this->hp = 1;
			break;
		case cauldron_ice:
			this->mImage = IMAGE->FindImage("cauldron_ice");
			this->hp = 1;
			break;
		}
		////////////////

	}

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	virtual void GetDamege(int amount) { 

		if (amount >= this->hp) {

			this->mAlive = false;
			switch (types)
			{
			case wall_dirt_crypt_diamond1:
			case wall_dirt_zone2_diamond1:
			case wall_dirt_zone3cold_diamond1:
			case wall_dirt_zone3HOT_diamond1:
			case wall_dirt_zone4_diamond1:
				MakeParticlesRandom("TEMP_particle_dirt", this->mCenter, PARTICLE_TYPE::DIG, 0.2f, 0.5f, 15, this);
				if (objectm->GetTile(this)->item == nullptr)
					objectm->GetTile(this)->item = new Item(ITEM_dirt_block);
				objectm->GetTile(this)->item->isStackable = true;
				break;
			}

		}
	}

	void DeadEvent()override;
};

