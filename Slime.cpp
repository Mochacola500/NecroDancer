#include "stdafx.h"
#include "Slime.h"


Slime::Slime()
{
}

Slime::Slime(MONSTER_TYPE type, Vector2 pos)
{
	Monster::Init();
	moveCount = 0;
	this->imageLocation = pos;
	this->mCenter = pos;
	this->mosnterType = type;
	string imageName;

	switch (mosnterType)
	{
	case BLUE_SLIME:
		this->hp = 20;
		this->power = 5;
		imageName = "slime_ice";
		break;
	case GREEN_SLIME:
		this->hp = 10;
		this->power = 1;
		imageName = "slime_green";
		break;
	case ORANGE_SLIME:
		this->hp = 20;
		this->power = 8;
		imageName = "slime_orange";
		break;
	default:
		break;
	}
	hpBar.Init(hp);
	this->image.Initialize(imageName, &imageLocation);
	mMoveEvent.Initialize(&imageLocation);
}


Slime::~Slime()
{
}

void Slime::Init()
{

}

void Slime::Update()
{
	Monster::Update();

	if (mosnterType == GREEN_SLIME)
	{
		mMoveEvent.Jump(6.0f);
	}
}

void Slime::Render()
{
	Monster::Render();
}

void Slime::Release()
{
}

void Slime::BeatUpdate()
{
	if (mosnterType == BLUE_SLIME)
	{
		if (direction == RIGHT)
		{
			Vector2 target(mCenter.x - TILESIZE_X, mCenter.y);
			this->direction = LEFT;
			if (objectm->CanMove(target, this)) {
				mMoveEvent.MoveOrder(LEFT);
				mCenter = target;
			}
			if (objectm->GetObjectPtr(target) != nullptr) {
				if (objectm->GetObjectPtr(target)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}
		}
		else
		{
			Vector2 target(mCenter.x + TILESIZE_X, mCenter.y);
			this->direction = RIGHT;
			if (objectm->CanMove(target, this)) {
				mMoveEvent.MoveOrder(RIGHT);
				mCenter = target;
				moveCount++;
			}
			if (objectm->GetObjectPtr(target) != nullptr) {
				if (objectm->GetObjectPtr(target)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}

		}
	}
	else if (mosnterType == ORANGE_SLIME)
	{
		switch (moveCount)
		{
		case 0:
			Vector2 target = Vector2(mCenter.x - TILESIZE_X, mCenter.y);
			this->direction = LEFT;
			if (objectm->CanMove(target, this)) {
				mMoveEvent.MoveOrder(LEFT);
				mCenter = target;
			}
			if (objectm->GetObjectPtr(target) != nullptr) {
				if (objectm->GetObjectPtr(target)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}

			break;
		case 1:
			Vector2 target2 = Vector2(mCenter.x, mCenter.y + TILESIZE_X);
			if (objectm->CanMove(target2, this)) {
				mMoveEvent.MoveOrder(DOWN);
				mCenter = target2;
			}
			if (objectm->GetObjectPtr(target2) != nullptr) {
				if (objectm->GetObjectPtr(target2)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target2)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target2, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}

			break;
		case 2:
			Vector2 target3 = Vector2(mCenter.x + TILESIZE_X, mCenter.y);
			this->direction = RIGHT;
			if (objectm->CanMove(target3, this)) {
				mMoveEvent.MoveOrder(RIGHT);
				mCenter = target3;
			}
			if (objectm->GetObjectPtr(target3) != nullptr) {
				if (objectm->GetObjectPtr(target3)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target3)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target3, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}

			break;
		case 3:
			Vector2 target4 = Vector2(mCenter.x, mCenter.y - TILESIZE_X);
			if (objectm->CanMove(target4, this)) {
				mMoveEvent.MoveOrder(UP);
				mCenter = target4;
			}
			if (objectm->GetObjectPtr(target4) != nullptr) {
				if (objectm->GetObjectPtr(target4)->type == ObjectType::PLAYER) {
					objectm->GetObjectPtr(target4)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", target4, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_slime_attack");
					CAMERA->Shake(2, 4);
				}
			}

			break;
		}

		moveCount++;

		if (moveCount > 3) {
			moveCount = 0;
		}
	}
}

void Slime::GetDamege(int amount)
{
	SOUND->Play("en_slime_hit_01");
	if (mosnterType == BLUE_SLIME) {
		MakeParticles("TEMP_particle_blue", this->mCenter, PARTICLE_TYPE::DIG, 0.2f, 0.5f, 8.f, 8, this);
	}
	else if (mosnterType == GREEN_SLIME)
	{
		MakeParticles("TEMP_particle_green", this->mCenter, PARTICLE_TYPE::DIG, 0.2f, 0.5f, 8.f, 8, this);
	}
	else if (mosnterType == ORANGE_SLIME)
	{
		MakeParticles("TEMP_particle_orange", this->mCenter, PARTICLE_TYPE::DIG, 0.2f, 0.5f, 8.f, 8, this);
	}
	Monster::GetDamege(amount);
	hpBar.NotifyHit(hp);
}

void Slime::DeadEvent()
{
	objectm->GetTile(this)->item = new Item(ITEM_coin,0, (rand() % 2 + 1) * coinMulti);
	DropTable(5);
	SOUND->Play("en_slime_death");

	if (mosnterType == BLUE_SLIME)
	{
		objectm->m_Particles.push_back(new Particle(image.GetName(), this->mCenter, PARTICLE_TYPE::DEAD));
		this->objectm->GetTile(this)->m_Image = IMAGE->FindImage("TEMP_floor_ice");
	}
	else
	{
		objectm->m_Particles.push_back(new Particle(image.GetName(), this->mCenter, PARTICLE_TYPE::DEAD));
	}
}
