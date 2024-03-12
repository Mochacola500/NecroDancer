#include "stdafx.h"
#include "Wall.h"


Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::Init()
{
}

void Wall::Update()
{
}

void Wall::Render()
{
	if (types == cauldron_coals || types == cauldron_ice)
	{
		this->mImage->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
		if (objectm->OnFog(mCenter)) 
		{
			this->mImage->Render(mCenter, Vector2(0, 1), true);
		}
		else
		{
			this->mImage->Render(mCenter, Vector2(0, 0), true);
		}
	}
	else
	{
		this->mImage->SetSize(Vector2(TILESIZE_X, TILESIZE_Y + 60));
		this->mImage->Render(Vector2(mCenter.x, mCenter.y - 35), true);
	}
}

void Wall::Release()
{
}

void Wall::DeadEvent()
{
	objectm->GetTile(this)->fire = false;
	if (types == cauldron_coals || types == cauldron_ice
		|| types == door_front || types == door_side)
	{
		switch (types)
		{
		case cauldron_coals:
			objectm->GetTile(this)->SetTileType(TILE_TYPE_TEMP_floor_hotcoal);
			break;
		case cauldron_ice:
			objectm->GetTile(this)->SetTileType(TILE_TYPE_TEMP_floor_ice);
			break;
		}
	}
}
