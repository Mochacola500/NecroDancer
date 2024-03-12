#pragma once
#include "Scene.h"

///////////////////////////////////////////////////////////////////////
// 크기 설정
const Vector2 MAIN_MENU_IMAGE_DRAW = { 0,0 };
const Vector2 MAIN_MENU_IMAGE_SIZE = { WINSIZE_X, WINSIZE_Y - 50 };

///////////////////////////////////////////////////////////////////////

enum Sellect
{
	start_scene,
	end_scene,
	option_scene,
	map_tool_scene
};

class Mainmenu :
	public Scene
{
private:
	float alpha;
	FloatRect rc;
	bool start;
	Image* image;
	Image* start_image;
	Image* end_image;
	Image* option_image;
	Image* map_tool_image;

	vector<Image*> images;

	Vector2 SELECT_BAR_SIZE;
	FloatRect SELECT_BAR_ALPHA;
	float speed;

	Sellect current;

public:
	Mainmenu() = default;
	~Mainmenu() = default;

	void Start() override {}
	void End() override {}

	void Init() override 
	{
		SOUND->Play("main_menu", 0.5f);
		alpha = 0.f;
		rc = { 0,0,WINSIZE_X, WINSIZE_Y };
		start = false;
		image = IMAGE->FindImage("mainmenu");
		start_image = IMAGE->FindImage("start");
		end_image = IMAGE->FindImage("end");
		option_image = IMAGE->FindImage("option");
		map_tool_image = IMAGE->FindImage("map_tool");
		SELECT_BAR_ALPHA = { 0, 500, 0, WINSIZE_Y - 70 };
		speed = 10.0f;
		current = start_scene;
	}
	void Release() override {
		SOUND->Stop("main_menu");
	}
	void Update() override
	{
		if(speed < 40.f)
		speed += 2.0f;

		if (SELECT_BAR_ALPHA.right < WINSIZE_X) {
			SELECT_BAR_ALPHA.right += speed;
		}
		if (KEY->IsOnceKeyDown(VK_SPACE))
		{
			SOUND->Play("sfx_ui_select_up");
			start = true;
		}
	}
	void Render() override
	{
		image->SetSize(MAIN_MENU_IMAGE_SIZE);
		image->Render(MAIN_MENU_IMAGE_DRAW);
		D2DRENDER->FillRectangle(SELECT_BAR_ALPHA, ColorF::Black, 0.4f);
		int left = 20;
		for (auto& render : images)
		{
			render->Render(
				static_cast<int>(WINSIZE_X / 2 - 70 + left),
				static_cast<int>(MAIN_MENU_IMAGE_SIZE.y - 150));
			left += 220;
		}

		start_image->SetSize(Vector2(200, 50));
		start_image->Render(
			static_cast<int>(WINSIZE_X / 2 - 90),
			static_cast<int>(MAIN_MENU_IMAGE_SIZE.y - 150));

		

		if (start)
		{
			alpha += 0.03f;
			D2DRENDER->FillRectangle(rc, ColorF::Black, alpha);
			if (alpha > 2 && current == map_tool_scene) {
				SCENE->ChangeScene("Test");
			}
			if (alpha > 2 && current == end_scene) {

			}
			if (alpha > 2 && current == start_scene) {
				SCENE->ChangeScene("Zone1");
			}
		}
	}
};

