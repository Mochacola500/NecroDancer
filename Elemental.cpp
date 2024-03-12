#include "stdafx.h"
#include "Elemental.h"


Elemental::Elemental(MONSTER_TYPE type, Vector2 pos)
{
	Monster::Init();
	this->imageLocation = pos;
	this->mCenter = pos;
	this->mosnterType = type;
	string imageName;
	MovePoint = 0;
	this->power = 1;
	switch (type)
	{
	case FIRE_ELEMENTAL:
		this->hp = 60;
		this->power = 15;
		imageName = "fire_elemental1";
		this->image.Initialize("fire_elemental1", &imageLocation);
		break;
	case ICE_ELEMENTAL:
		this->hp = 60;
		this->power = 15;
		imageName = "ice_elemental1";
		this->image.Initialize("ice_elemental1", &imageLocation);
		break;
	}
	hpBar.Init(hp);
	mMoveEvent.Initialize(&imageLocation);
}

Elemental::~Elemental()
{
}

void Elemental::Init()
{
}

void Elemental::Update()
{
	Monster::Update();
}

void Elemental::Render()
{
	Monster::Render();
}

void Elemental::Release()
{
}

void Elemental::BeatUpdate()
{

	if (objectm->PlayerStay() && objectm->IsPlayerNearBy(mCenter, 10))
	{
		if (MovePoint == 0)
		{
			followList = objectm->PathFinder(this->GetCenter(), objectm->GetPlayerCenter());

			if (objectm->CanMove(followList, this))
			{
				if (objectm->GetPlayerCenter().x > this->mCenter.x)
				{
					this->direction = RIGHT;
				}
				else
				{
					this->direction = LEFT;
				}

				mMoveEvent.MoveOrder(mCenter, followList);
				if (this->mosnterType == FIRE_ELEMENTAL)
				{
					objectm->GetTile(followList)->SetTileType(TILE_TYPE_TEMP_floor_hotcoal);
				}
				else {
					objectm->GetTile(followList)->SetTileType(TILE_TYPE_TEMP_floor_ice);
				}
				mCenter = followList;
			}
			if (objectm->GetObjectPtr(followList) != nullptr)
			{
				if (objectm->GetObjectPtr(followList)->type == ObjectType::PLAYER)
				{
					objectm->GetObjectPtr(followList)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", followList, PARTICLE_TYPE::ATTACK));
					SOUND->Play("en_bat_attack");
					CAMERA->Shake(2, 4);
				}
			}
			MovePoint += 2;
		}
		else
		{
			MovePoint--;
		}
	}

}

void Elemental::GetDamege(int amount)
{
	this->mosnterType == FIRE_ELEMENTAL ?
	MakeParticles("TEMP_particle_red", this->mCenter, PARTICLE_TYPE::HIT, 0.2f, 0.5f, 8.f, 7, this) :
	MakeParticles("TEMP_particle_blue", this->mCenter, PARTICLE_TYPE::HIT, 0.2f, 0.5f, 8.f, 7, this);

	Monster::GetDamege(amount);
	hpBar.NotifyHit(hp);
}

void Elemental::DeadEvent()
{
	objectm->GetTile(this)->item = new Item(ITEM_coin, 0, (rand() % 2 + 20) * coinMulti);
	DropTable(25);
	objectm->m_Particles.push_back(new Particle(image.GetName(), this->mCenter, PARTICLE_TYPE::DEAD));
}
