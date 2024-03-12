#include "stdafx.h"
#include "Door.h"


Door::Door(WALL_TYPE types, Vector2 location)
{
	Object::Init();
	this->types = types;
	this->imageLocation = location;
	this->mCenter = location;

	switch (types)
	{
	case door_front:
		mImage = IMAGE->FindImage("door_front");
		break;
	case door_side:
		mImage = IMAGE->FindImage("door_side");
		break;
	}
	this->type = WALL;
}

void Door::Render()
{
	this->mImage->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
	this->mImage->Render(imageLocation, true);
}

void Door::Update()
{

}
