#pragma once
#include "Monster.h"
class Elemental :
	public Monster
{
private:
	Vector2 followList;
	int MovePoint;
public:
	Elemental() = default;
	Elemental(MONSTER_TYPE type, Vector2 pos);
	~Elemental();


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void BeatUpdate() override;
	void GetDamege(int amount) override;
	void DeadEvent() override;
};

