#pragma once
#include "Object.h"

class Tresure :
	public Monster
{
private:
	MONSTER_TYPE objectTt;
public:
	Tresure() = default;
	Tresure(MONSTER_TYPE, Vector2);
	~Tresure() = default;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void BeatUpdate() override;
	void GetDamege(int amount) override;
	void DeadEvent() override;
};

