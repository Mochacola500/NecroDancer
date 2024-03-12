#pragma once

namespace TILE_IDENTIFY
{
	enum class Enum
	{
		FLOOR,
		WALL,
		LAVA,
		STAIR,
		NONE
	};

	enum class State
	{
		FLOW,
		NONE
	};
	
	// Enum 에 따른 이미지 변경
	inline Enum InfoTable(const string& info)
	{
		if (info.find("floor"))
		{
			return Enum::FLOOR;
		}
		else if (info.find("wall"))
		{
			return Enum::WALL;
		}
		else if (info.find("lava"))
		{
			return Enum::LAVA;
		}
		else if (info.find("stair"))
		{
			return Enum::STAIR;
		}
	}

	inline State StateTable(const string& info)
	{
		if(info.find("lava"))
		{ 
			return State::FLOW;
		}
		else
		{
			return State::NONE;
		}
	}

	
}