#pragma once
#include "Object.h"

extern bool activeMove;
extern bool dododo;

class Player : public Object
{
public:
	Direction direction;
	Direction pastDirection;
	MoveEvent camera;

	float speed;

	int fliping;
	int flipingCount;
	bool isFlip;
	bool onceFill;

	Player() = default;
	Player(Vector2 location);
	~Player() {}


	void Init() override {}
	void Update() override;
	void Render() override;
	void Release() override;
	
	void Interaction(Direction dir);
	bool DamegeTarget(Vector2 target, bool effect = true, Vector2 size = {TILESIZE_X, TILESIZE_Y},float anlge = 0.f);
	Vector2 AttackIndex(Vector2 y);
	bool GetPlayer()override { return true; }
	void GetDamege(int amount) override;
	void BeatUpdate() override;
};