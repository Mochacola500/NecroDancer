#pragma once
#include "SingletonBase.h"

class UI 
	: public SingletonBase<UI>
{
protected:
	friend class SingletonBase<UI>;
	Image* hearts;
	Image* half_hearts;
	Image* coins;
	Image* daimond;
	NumberPrint coinCount;
	NumberPrint daimondCount;

	Vector2 pos;
	float right;
	Vector2 UI_Size;

	int value;
	int timer;

	Vector2 location;
	Vector2 daipos;
	bool doo;
	float speed;
	float daimondAlpha;
public:
	int hitt;

	void ValueUp() {

		value++;

		if (DATA->hp / 10 <= value) {
			value = 0;
		}

		this->timer = 8;
	}

	void ShootDiamond(Vector2 pos)
	{
		this->location = pos;
		doo = true;
		daimondAlpha = 1.0f;
	}

	UI() = default;
	~UI() = default; 

	void Init()
	{
		this->daimond = IMAGE->FindImage("diamond");
		this->coins = IMAGE->FindImage("hud_coins");
		this->hearts = IMAGE->FindImage("heart");
		this->half_hearts = IMAGE->FindImage("heart_empty");
		location = { 0,0 };
		INVEN->Init();
		coinCount.Init();
		daimondCount.Init();

		UI_Size = { TILESIZE_X, TILESIZE_Y };
		daipos = {1225, 175};
		right = UI_Size.x + 10;
		value = 0;
		timer = 0;
		hitt = 0;
		doo = false;

		speed = 10.0f;
		daimondAlpha = 1.0f;
	}

	void Update()
	{}

	void ReserveHit()
	{
		if (hitt) {
			GetHit(static_cast<float>(0.1f * (hitt + 2)));
			hitt--;
		}
	}


	void GetHit(float alpha)
	{
		D2DRENDER->FillRectangle(FloatRect(-20, -20, WINSIZE_X + 20, WINSIZE_Y + 20), ColorF::Red, alpha);
	}
	
	void Render()
	{
	
			ReserveHit();

			if (doo) {
				daimond->SetAlpha(daimondAlpha);
				daimond->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
				daimond->Render(location);

				float angle = SetAngle(location, daipos);
				location.x += cosf(angle) * speed;
				location.y -= sinf(angle) * speed;
				daimondAlpha -= 0.02f;
				speed += 0.1f;

				if (location.x > daipos.x - 5.f &&
					location.y > daipos.y - 5.f) {
					doo = false;
				}
			}

			pos = { static_cast<int>(1375 - DATA->maxhp / 10 * right), 6 };

			Vector2 Size = UI_Size;

			for (int i = 0; i < DATA->maxhp / 10; ++i) {
				if (i != value) {
					Size = UI_Size;
				}
				else {
					if (timer > 0 && DATA->hp > 0) {
						Size = UI_Size + 10;
						timer--;
					}
					else {
						Size = UI_Size;
					}
				}
				if ((DATA->hp + 1) / 10 < i + 1) {
					half_hearts->SetSize(Size);
					half_hearts->Render(
						Vector2
						(
							pos.x - (UI_Size.x / 2) - half_hearts->GetSize().x / 2,
							pos.y - (UI_Size.y / 2) - +half_hearts->GetSize().y / 2 + 80
						)
					);
				}
				else
				{
					hearts->SetSize(Size);
					hearts->Render(
						Vector2
						(
							pos.x - (UI_Size.x / 2) - hearts->GetSize().x / 2,
							pos.y - (UI_Size.y / 2) - +hearts->GetSize().y / 2 + 80
						)
					);
				}

				pos.x += right;
			}

			coins->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
			coins->Render(Vector2(1225, 100));

			daimond->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
			daimond->Render(daipos);

			coinCount.Render(Vector2(1320, 120), DATA->coin, Vector2(25, 25));
			daimondCount.Render(Vector2(1320, 195), DATA->daimond, Vector2(25, 25));

			INVEN->Render();
		}
	
};

#define UIS UI::Get()