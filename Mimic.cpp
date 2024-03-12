#include "stdafx.h"
#include "Mimic.h"


Mimic::Mimic(MONSTER_TYPE type, Vector2 pos)
{
	Monster::Init();
	moveCount = 0;
	this->imageLocation = pos;
	this->mCenter = pos;
	this->mosnterType = type;
	string imageName;
	sight = 5;
	wake = false;
	switch (mosnterType)
	{
	case cauldron_coals_mimic:
		this->hp = 30;
		this->power = 5;
		imageName = "cauldron_coals_mimic";
		break;
	case cauldron_ice_mimic:
		this->hp = 30;
		this->power = 5;
		imageName = "cauldron_ice_mimic";
		break;
	}
	hpBar.Init(hp);
	this->image.Initialize(imageName, &imageLocation);
	mMoveEvent.Initialize(&imageLocation);
}

void Mimic::Init()
{
}

void Mimic::Update()
{
	Monster::Update();
}

void Mimic::Render()
{
	if (this->objectm->OnFog(this->mCenter)) {
		this->image.SetDrawLocation(1);
	}
	else {
		this->image.SetDrawLocation(0);
	}
	if (wake)
	{
		image.Render(direction);
		hpBar.Render(imageLocation);
	}
	else
	{
		image.FrameRender(Vector2(0, 0));
	}
}

void Mimic::Release()
{
}

void Mimic::BeatUpdate()
{
	if (objectm->PlayerStay() && objectm->IsPlayerNearBy(mCenter, sight))
	{
		wake = true;
		if (moveCount == 0)
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
				mCenter = followList;
			}
			if (objectm->GetObjectPtr(followList) != nullptr)
			{
				if (objectm->GetObjectPtr(followList)->type == ObjectType::PLAYER)
				{
					objectm->GetObjectPtr(followList)->GetDamege(this->power);
					objectm->m_Particles.push_back(new Particle("swipe_enemy", followList, PARTICLE_TYPE::ATTACK));
					CAMERA->Shake(2, 4);
				}
			}
			moveCount += 2;
		}
		else
		{
			moveCount--;
		}
	}
}

void Mimic::GetDamege(int amount)
{
	Monster::GetDamege(amount);
	hpBar.NotifyHit(hp);
}

void Mimic::DeadEvent()
{
	switch (mosnterType)
	{
	case cauldron_coals_mimic:
		objectm->GetTile(Vector2(mCenter.x,
				mCenter.y))->SetTileType(TILE_TYPE_TEMP_floor_hotcoal);
		break;
	case cauldron_ice_mimic:
			objectm->GetTile(Vector2(mCenter.x,
				mCenter.y))->SetTileType(TILE_TYPE_TEMP_floor_ice);
		break;
	}
	DropTable(10);
}
