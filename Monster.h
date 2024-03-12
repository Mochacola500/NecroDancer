#pragma once
#include "Object.h"

struct MonsterHp
{
	int maxHp;
	int currentHp;

	MonsterHp() {}
	
	void Init(int hp) { this->maxHp = currentHp = hp; }

	void Render(Vector2 location)
	{
		Vector2 position(location);
		position.x = position.x + (TILESIZE_X / 2) - maxHp;
		Vector2 heart(25, 25);
		position.y -= 5;
		//(DATA->hp + 1) / 10 < i + 1
		for (int i = 0; i < maxHp / 10; ++i) {
			if ((currentHp + 1) / 10 < i + 1) {
				IMAGE->FindImage("TEMP_heart_empty_small")->SetSize(heart);
				IMAGE->FindImage("TEMP_heart_empty_small")->Render(position, true);
			}
			else
			{
				IMAGE->FindImage("TEMP_heart_small")->SetSize(heart);
				IMAGE->FindImage("TEMP_heart_small")->Render(position, true);
			}
			position.x += heart.x;
		}
	}

	void NotifyHit(int hp)
	{
		currentHp = hp;
	}
};

class Monster :
	public Object
{
protected:
	Direction direction;
	MonsterHp hpBar;

public:
	MONSTER_TYPE mosnterType;

	Monster();
	virtual ~Monster();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	virtual void GetDamege(int amount) override;
	virtual void DeadEvent(){}
	virtual void DamegePlayer(Vector2 target, string imageName);
	virtual bool MoveThere(Direction dir, Vector2 target);

	virtual void DropTable(float add);
	virtual bool ItemDrop(Tile* p, float& add);
	virtual bool GoldDrop(Tile* p, float& add);
};

