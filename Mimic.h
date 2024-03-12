#pragma once
#include "Monster.h"
class Mimic :
	public Monster
{
private:
	Vector2 followList;
	int moveCount;
	bool wake;
	int sight;

public:
	Mimic() = default;
	~Mimic() = default;

	Mimic(MONSTER_TYPE type, Vector2 pos);


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void BeatUpdate() override;
	void GetDamege(int amount) override;
	void DeadEvent() override;
};

