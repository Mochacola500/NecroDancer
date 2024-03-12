#pragma once
#include "Monster.h"
class Bat :
	public Monster
{
private:
	int time;
public:
	Bat() = default;
	Bat(MONSTER_TYPE type, Vector2 pos);
	~Bat() = default;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void BeatUpdate() override;
	void GetDamege(int amount) override;
	void DeadEvent() override;
};

