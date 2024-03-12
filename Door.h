#pragma once
#include "Wall.h"

class Door :
	public Wall
{
public:
	Door() = default;
	Door(WALL_TYPE types, Vector2 location);
	~Door() = default;

	void Render() override;
	void Update() override;
};

