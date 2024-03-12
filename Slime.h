#pragma once
#include "Monster.h"
class Slime :
	public Monster
{
private:
	int moveCount;
public:
	Slime();
	Slime(MONSTER_TYPE type, Vector2 pos);
	~Slime();


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void BeatUpdate() override;
	void GetDamege(int amount) override;
	void DeadEvent() override;
};

