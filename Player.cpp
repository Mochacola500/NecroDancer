#include "stdafx.h"
#include "Player.h"

bool activeMove;
bool dododo;



Player::Player(Vector2 location)
{
	Object::Init();
	this->type = PLAYER;

	this->head.Initialize("player1_heads_xmas", &mCenter);
	this->torso.Initialize("player1_armor_body_xmas", &mCenter);

	mMoveEvent.Initialize(&mCenter);
	camera.Initialize(&CameraLocation);
	pastDirection = LEFT;
	isFlip = false;

	this->mCenter = location;
	this->imageLocation = location;

	if (inGame)
		CameraLocation = mCenter;

	this->currentItem = nullptr;
	this->currentArmor = nullptr;
	this->currentShov = nullptr;

	INVEN->GetPlayer(this);

	INVEN->AddItem(new Item(ITEM_weapon_broadsword, 0));
	INVEN->AddItem(new Item(ITEM_shovel_basic, 0));

	dododo = false;
	onceFill = true;
}

void Player::Update()
{
	if (activeMove) {
		if (currentArmor == nullptr)
		{
			torso.SetDrawLocation(0);
		}

		if (KEY->IsOnceKeyDown('A') && mMoveEvent.MoveCompleteCheck()) {
			this->direction = LEFT;
			dododo = true;
			pastDirection = LEFT;
			Interaction(LEFT);
		}
		else if (KEY->IsOnceKeyDown('D') && mMoveEvent.MoveCompleteCheck()) {
			this->direction = RIGHT;
			dododo = true;
			pastDirection = RIGHT;
			Interaction(RIGHT);
		}
		else if (KEY->IsOnceKeyDown('W') && mMoveEvent.MoveCompleteCheck()) {
			dododo = true;
			pastDirection = UP;
			Interaction(UP);
		}
		else if (KEY->IsOnceKeyDown('S') && mMoveEvent.MoveCompleteCheck()) {
			dododo = true;
			pastDirection = DOWN;
			Interaction(DOWN);
		}


		if (mMoveEvent.MoveCompleteCheck())
		{
			if (objectm->GetTile(this)->tileType == TILE_TYPE_TEMP_floor_ice) {
				if (objectm->CanMove(DirectionAxis(pastDirection, 1, 0), this))
				{
					mMoveEvent.MoveOrder(pastDirection);
					camera.MoveOrder(pastDirection);
					onceFill = true;
					mMoveEvent.jumpDo = false;
					return; // ¹Ì²ô·¯Áü
				}
			}
		}
	}
	if (mMoveEvent.MoveCompleteCheck())
	{
		OBJECT->Fill(this, 6 + INVEN->light);
		mMoveEvent.jumpDo = true;
	}

	this->mMoveEvent.Update();
	this->camera.UpdateN();

}

void Player::Render()
{
	if (fliping > 0) {
		if (flipingCount < 6) {
			torso.SetAlpha(1.0f);
			head.SetAlpha(1.0f);
			flipingCount++;
		}
		else
		{
			fliping--;
			flipingCount = 0;

			torso.SetAlpha(isFlip ? 0.2f : 1.0f);
			head.SetAlpha(isFlip ? 0.2f : 1.0f);

			isFlip ? isFlip = false : isFlip = true;
		}

	}
	else
	{
		torso.SetAlpha(1.0f);
		head.SetAlpha(1.0f);
	}

	torso.Render(direction);
	head.Render(direction);
}

void Player::Release()
{

}

void Player::GetDamege(int amount)
{
	SOUND->Play("sfx_player_hit_ST");
	MakeParticles("TEMP_particle_red", this->mCenter, PARTICLE_TYPE::HIT, 0.2f, 0.5f, 8.f, 7, this);

	int defense = 0;
	if (currentArmor != nullptr)
		defense = currentArmor->defense;
	int damege = (amount - defense);
	if (damege > 0)DATA->hp -= damege;

	fliping = 5;
	flipingCount = 0;
	isFlip = true;
	UIS->hitt = 3;

	if (currentItem != nullptr)
	{
		switch (currentItem->itemType)
		{
		case ITEM_weapon_longsword_glass:
		case ITEM_weapon_rapier_glass:
		case ITEM_weapon_dagger_glass:
		case ITEM_weapon_broadsword_glass:
			SAFE_DELETE(currentItem);
			Item* glass = new Item(ITEM_weapon_dagger_shard);
			INVEN->weaphon = glass;
			currentItem = glass;
			break;
		}
	}

	// »ç¸ÁÇÔ¼ö

	//if (DATA->hp <= 0) {
	//	this->mAlive = false;
	//	CAMERA->SetState(CAMERA_STATE::FREE);
	//}
}

void Player::BeatUpdate()
{
	static int time = 2;
	if (time != 2)
	{
		if (mMoveEvent.MoveCompleteCheck())
		{
			if (objectm->GetTile(this)->tileType == TILE_TYPE_TEMP_floor_hotcoal)
			{
				this->GetDamege(5);
				MakeParticlesRandom("fire0", mCenter, PARTICLE_TYPE::HIT, 0.5f, 0, 20, this);
				time = 0;
				return; // À¸¾Ç ¶ß°Å
			}
		}
		time++;
	}
}
