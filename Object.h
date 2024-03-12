#pragma once

enum DoorType
{
	WOOD,
	METAL
};

enum Trap
{
	TRAP_UP,
	TRAP_LEFT,
	TRAP_DOWN,
	TRAP_NONE
};

enum WALL_TYPE
{
	//////////////////////////////////////
	// 단일 이미지

	// 마지막벽
	end_of_world,
	// 공용 : 상점 및 돌벽
	wall_shop_crypt,
	wall_shop_crypt_dark_cracked,
	wall_dirt_crypt_diamond1,
	wall_stone_crypt,
	// 존 1
	zone1_catacomb_cracked,
	wall_catacomb_crypt1,
	wall_catacomb_crypt2,
	zone1_wall_dirt_cracked,
	zone1_wall_stone_cracked,
	// 존 2
	zone2_wall_stone,
	zone2_wall_dirt_crack,
	zone2_wall_stone_crack,
	wall_dirt_zone2_diamond1,
	// 존 3
	zone3_wall_stone_cold,
	zone3_wall_stone_hot,
	wall_dirt_zone3cold_diamond1,
	wall_dirt_zone3HOT_diamond1,

	// 존 4
	zone4_wall_catacomb_A,
	zone4_wall_rock_A,
	wall_dirt_zone4_diamond1,

	//5 1 프레임 이미지
	necrodancer_wall,
	boss_wall,
	door_front,
	door_side,
	cauldron_coals,
	cauldron_ice,
	end_of_wall_type
};

enum MONSTER_TYPE
{
	BLUE_SLIME,
	GREEN_SLIME,
	ORANGE_SLIME,
	BAT,
	BAT_BLACK,
	BAT_GREEN,
	BAT_RED,
	FIRE_ELEMENTAL,
	ICE_ELEMENTAL,
	CHEST,
	CHEST_BLACK,
	CHEST_WHITE,
	cauldron_coals_mimic,
	cauldron_ice_mimic,

	end_of_monster_type,
	player_monster_type
};

enum State
{
	MOVE,
	ATTACK,
	IDLE
};

class ItemInterface;

class ObjectManager;

class Object
{
protected:
	int hp;
	int power;

	Vector2 mCenter;
	Vector2 mImagelocation;
	Vector2 mMoveTable;
	bool mAlive;
	State state;
	bool isPlayer;

public:
	Vector2 imageLocation;
	Animation image;
	Animation head;
	Animation torso;
	MoveEvent mMoveEvent;
	Vector2 CameraLocation;
	Image* mImage;
	Vector2 Size;
	Vector2 start;
	ObjectManager* objectm;
	ObjectType type;

	ItemInterface* currentItem;
	ItemInterface* currentArmor;
	ItemInterface* currentShov;

	Object() = default;
	virtual ~Object() = default;

	virtual void DeadEvent() {}
	virtual float GetAxis(Direction dir);
	virtual Vector2 Rotation(Direction dir, Vector2 size);

	virtual Vector2 DirectionAxis(Direction dir, int x, int y);
	virtual Vector2 DirectionAxisImage(Direction dir, int x, int y);
	virtual bool GetPlayer() { return false; }
	virtual Vector2 GetCenter()const { return mCenter; }
	virtual void SetCenter(Vector2 center) { mCenter = center; }
	virtual bool GetAlive() const { return mAlive; }
	virtual void SetAlive(bool alive) { mAlive = alive; }
	virtual string GetImageNaem() const { if (mImage != nullptr) { return mImage->GetKey(); } return ""; }
	virtual void Init()
	{

		this->mImage = nullptr;
		this->mCenter = { 0.f, 0.f };
		this->mAlive = true;
		this->state = State::IDLE;
		this->mMoveTable = { 0.f,0.f };
		this->type = OBJECT_TYPE_END;

	}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	virtual void BeatUpdate() {}

	virtual void GetDamege(int amount) { hp -= amount; if (hp < 0) this->mAlive = false; }
	virtual int GetPower() const { return power; }

	virtual Vector2 GetIndex() { return Vector2(mCenter.x / TILESIZE_X, mCenter.y / TILESIZE_Y); }
};
