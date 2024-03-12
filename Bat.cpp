#include "stdafx.h"
#include "Bat.h"

Bat::Bat(MONSTER_TYPE type, Vector2 pos)
{
	Monster::Init();
	this->mosnterType = type;
	this->imageLocation = pos;
	switch (mosnterType)
	{
	case BAT:
		this->hp = 10;
		this->image.Initialize("bat", &imageLocation);
		break;
	case BAT_BLACK:
		this->hp = 20;
		this->image.Initialize("bat_black", &imageLocation);
		break;
	case BAT_GREEN:
		this->hp = 20;
		this->image.Initialize("bat_green", &imageLocation);
		break;
	case BAT_RED:
		this->hp = 30;
		this->image.Initialize("bat_red", &imageLocation);
		break;
	}

	hpBar.Init(hp);
	this->mCenter = pos;

	this->power = 10;
	this->time = 0;
	mMoveEvent.Initialize(&imageLocation);
}

void Bat::Init()
{
}

void Bat::Update()
{
	mMoveEvent.UpdateMoveTarget();
}

void Bat::Render()
{
	Monster::Render();
}

void Bat::Release()
{
}

void Bat::BeatUpdate()
{
	if (time == 2)
	{
		Direction direction = static_cast<Direction>(rand() % 4);
		if (MoveThere(direction, DirectionAxisImage(direction, 1, 0)))
		{

		}
		else
		{
			DamegePlayer(DirectionAxis(direction, 1, 0), "");
		}

		time = 1;
	}
	else
	{
		time++;
	}
}

void Bat::GetDamege(int amount)
{
	SOUND->Play("en_bat_hit");
	MakeParticles("TEMP_particle_red", this->mCenter, PARTICLE_TYPE::HIT, 0.2f, 0.5f, 8.f, 7, this);
	Monster::GetDamege(amount);
	hpBar.NotifyHit(hp);
}

void Bat::DeadEvent()
{
	SOUND->Play("en_bat_death");
	objectm->GetTile(this)->item = new Item(ITEM_coin, 0, (rand() % 2 + 3) * coinMulti);
	DropTable(10);
	objectm->m_Particles.push_back(new Particle(image.GetName(), this->mCenter, PARTICLE_TYPE::DEAD));
}
