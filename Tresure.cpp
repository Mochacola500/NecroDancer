#include "stdafx.h"
#include "Tresure.h"


Tresure::Tresure(MONSTER_TYPE type, Vector2 locate)
{
	Object::Init();
	this->mCenter = locate;
	imageLocation = locate;
	string imageName;
	this->type = MONSTER;
	this->objectTt = type;
	switch (objectTt)
	{
	case CHEST:
		this->hp = 1;
		imageName = "chest";
		break;
	case CHEST_BLACK:
		this->hp = 1;
		imageName = "chest_black";
		break;
	case CHEST_WHITE:
		this->hp = 1;
		imageName = "chest_white";
		break;
	default:
		break;
	}
	this->image.Initialize(imageName, &imageLocation);
}

void Tresure::Init()
{
}

void Tresure::Update()
{
}

void Tresure::Render()
{
	if (this->objectm->OnFog(this->mCenter)) {
		this->image.SetDrawLocation(1);
	}
	else {
		this->image.SetDrawLocation(0);
	}
	image.Render(RIGHT);
}

void Tresure::Release()
{
}

void Tresure::BeatUpdate()
{
}

void Tresure::GetDamege(int amount)
{
	if (amount > 0) {
		this->mAlive = false;
	}
}

void Tresure::DeadEvent()
{
	int dritem = rand() % end_of_equal;
	switch (objectTt)
	{
	case CHEST:
		objectm->GetTile(this)->item = new Item(static_cast<ItemType>(dritem), 30);
		break;
	case CHEST_BLACK:
		objectm->GetTile(this)->item = new Item(static_cast<ItemType>(dritem), 50);
		break;
	case CHEST_WHITE:
		objectm->GetTile(this)->item = new Item(static_cast<ItemType>(dritem), 70);
		break;
	default:
		break;
	}
}

