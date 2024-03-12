#include "stdafx.h"
#include "Monster.h"


void Monster::DamegePlayer(Vector2 target, string imageName)
{
	// 포인터 오버헤드를 피하기 위한 임시 포인터 변수
	Object* dealTo = objectm->GetObjectPtr(target);

	if (dealTo != nullptr && dealTo->type == PLAYER) { // 서순 주의. null을 가리킬 수 있음.
		int dealing = rand() % static_cast<int>(this->power * 0.7f) + this->power * 0.3f;
		dealTo->GetDamege(dealing);
		if (imageName != "") { objectm->m_Particles.push_back(new Particle(imageName, target, PARTICLE_TYPE::ATTACK)); }
		TextEvent* damege = new TextEvent(to_wstring(dealing), 35.f, ColorF::Red);
		damege->SetEvent(Vector2(target.x + 30, target.y), TextOption::DamegeFont, 0.1f, 140);
		objectm->m_TextEventS.push_back(damege);
	}
}

bool Monster::MoveThere(Direction dir, Vector2 target)
{
	if (dir == LEFT) this->direction = LEFT;
	if (dir == RIGHT) this->direction = RIGHT;

	if (objectm->CanMove(Vector2(mCenter + (target * TILESIZE_X)), this)) {
		mMoveEvent.MoveOrder(dir, target);
		mCenter = mCenter + (target * TILESIZE_X);
		return true;
	}
	return false;
}

void Monster::DropTable(float add)
{
	Vector2 temp;
	stack<Tile*> tempTile;

	float dropValue = add;
	for (int i = 0; i < 9; ++i) {
		temp.x = mCenter.x + xdx[i] * TILESIZE_X;
		temp.y = mCenter.y + xdy[i] * TILESIZE_Y;
		tempTile.push(objectm->GetTile(temp));
	}

	while (tempTile.size() != 0)
	{
		if (dropValue < 0) {
			break;
		}
		if (tempTile.top()->p == nullptr && tempTile.top()->item == nullptr)
		{
			if (ItemDrop(tempTile.top(), dropValue)) {
				tempTile.pop();
			}
			if (tempTile.top()->p == nullptr && tempTile.top()->item == nullptr)
			{
				if(GoldDrop(tempTile.top(), dropValue)) {
					tempTile.top();
				}
			}
		}
		dropValue--;
	}
}

bool Monster::ItemDrop(Tile* p, float& add)
{
	int get = rand() % 100 + 1;
	if (get < 5)
	{
		add -= get;
		int dritem = rand() % end_of_equal;
		p->item = new Item(static_cast<ItemType>(dritem), add);
		return true;
	}
	add--;
	return false;
}

bool Monster::GoldDrop(Tile* p, float& add)
{
	int get = rand() % 100 + (1 + add);
	if (get < 20 && add > 0)
	{
		int gold = rand() % static_cast<int>(add + 1);
		if (gold > 0)
		{
			p->item = new Item(ITEM_coin, add, gold *= coinMulti);
			add -= 5;
			return true;
		}
	}
	add--;
	return false;
}


Monster::Monster()
{
}


Monster::~Monster()
{
}

void Monster::Init()
{
	Object::Init();
	type = MONSTER;
}

void Monster::Update()
{
	
	this->mMoveEvent.Update();
}

void Monster::Render()
{
	if (this->objectm->OnFog(this->mCenter)) {
		this->image.SetDrawLocation(1);
	}
	else {
		this->image.SetDrawLocation(0);
	}
	image.Render(direction);
	hpBar.Render(imageLocation);
}

void Monster::Release()
{
}

void Monster::GetDamege(int amount)
{
	hp -= amount;

	if (hp <= 0)
	{
		this->mAlive = false;
	}
}
