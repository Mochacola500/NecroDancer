#pragma once
#include "SingletonBase.h"

extern int coinMulti;
extern int coinComboCount;

class Data
	: public SingletonBase<Data>
{
public:
	int maxhp;
	int hp;
	int coin;
	int daimond;

	Data()
	{
		maxhp = 30;
		hp = 30;
		coin = 0;
		daimond = 0;

	}

	void GainHp(int amount)
	{
		hp += amount;
		if (maxhp < hp) hp = maxhp;
	}

	~Data() {
	}

};
#define DATA Data::Get()