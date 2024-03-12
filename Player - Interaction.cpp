#include "stdafx.h"
#include "Player.h"

// 대미지 타겟이 존재하고 벽이 아니면 피해와 이벤트 생성
bool Player::DamegeTarget(Vector2 target, bool effect, Vector2 size, float angle)
{
	// 포인터 오버헤드를 피하기 위한 임시 포인터 변수
	Object* dealTo = objectm->GetObjectPtr(target);

	if (dealTo != nullptr && dealTo->type != WALL) { // 서순 주의. null을 가리킬 수 있음.
		int dealing = rand() % static_cast<int>(this->currentItem->power * 0.7f) + this->currentItem->power * 0.3f;
		dealTo->GetDamege(dealing);
		TextEvent* damege = new TextEvent(dealing);
		damege->SetEvent(Vector2(target.x + 30, target.y));
		objectm->m_TextEventS.push_back(damege);

		return true;
	}
	return false;
}

struct Once
{
	string musicName;
	int shapeflow;
	int shakey;
	bool check;

	Once() :
		check(false){}
	
	void Check(bool _check)
	{
		if (_check && !check)
		{
			this->check = true;
		}
	}
	
	bool OnceCheck()
	{
		return check;
	}
};

// 인덱스를 입력하면 해당방향을 가져옴
Vector2 Player::AttackIndex(Vector2 location)
{
	return Vector2(mCenter.x + location.x * TILESIZE_X, mCenter.y + location.y * TILESIZE_Y);
}

void Player::Interaction(Direction dir)
{
	Object* va = nullptr;
	va = objectm->GetObjectPtr(DirectionAxis(dir, 1, 0));

	Once onceAttackSucess;

	if (va != nullptr && va->type == WALL)
	{
		WALL_TYPE type = dynamic_cast<Wall*>(va)->types;
		if (type == door_front || type == door_side ||
			type == cauldron_coals || type == cauldron_ice)
		{
			va->SetAlive(false);
		}
		else if (currentShov != nullptr) // 삽을 장착 중일 경우
		{
			va->GetDamege(this->currentShov->power);
			objectm->m_Particles.push_back(new Particle(
				currentShov->effect, 
				va->imageLocation,
				PARTICLE_TYPE::SHOVING));

			if (va->GetAlive() == false)
			{
				CAMERA->Shake(5, 6);
				onceFill = true;
			}
		}
	}
	else if (this->currentItem != nullptr) // 무기 장착중일 경우,
	{
		switch (currentItem->itemType)
		{
			/* 브로드 소드 */
		case ITEM_weapon_broadsword_blood:
			DATA->GainHp(2); // 흡혈
		case ITEM_weapon_broadsword:
		case ITEM_weapon_broadsword_glass:
		case ITEM_weapon_broadsword_golden:
		case ITEM_weapon_broadsword_obsidian:
		case ITEM_weapon_broadsword_titanium:
			// 전방 3칸 공격
			onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1,  0)));
			onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1,  1)));
			onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1, -1)));
		
			if (onceAttackSucess.OnceCheck()) 
			{
				if (dir == LEFT)
				{
					objectm->m_Particles.push_back(new Particle(currentItem->effect,
						Vector2(mCenter.x, mCenter.y + 2 * TILESIZE_X),
						PARTICLE_TYPE::ATTACK,
						Vector2(60, 180),
						GetAxis(dir)));
				}
				if (dir == RIGHT)
				{
					objectm->m_Particles.push_back(new Particle(currentItem->effect,
						Vector2(mCenter.x + TILESIZE_X, mCenter.y - TILESIZE_X),
						PARTICLE_TYPE::ATTACK,
						Vector2(60, 180),
						GetAxis(dir)));
				}
				if (dir == UP)
				{
					objectm->m_Particles.push_back(new Particle(currentItem->effect,
						Vector2(mCenter.x - TILESIZE_X, mCenter.y),
						PARTICLE_TYPE::ATTACK,
						Vector2(60, 180),
						GetAxis(dir)));
				}
				if (dir == DOWN)
				{
					objectm->m_Particles.push_back(new Particle(currentItem->effect,
						Vector2(mCenter.x + 2 * TILESIZE_X, mCenter.y + TILESIZE_X),
						PARTICLE_TYPE::ATTACK,
						Vector2(60, 180),
						GetAxis(dir)));
				}

				SOUND->Play("sfx_player_hit_ST");
				CAMERA->Shake(5, 6);
			}
			break;

			/* 단검 */
		case ITEM_weapon_dagger_blood:
			DATA->GainHp(1); // 흡혈
		case ITEM_weapon_dagger:
		case ITEM_weapon_dagger_glass:
		case ITEM_weapon_dagger_golden:
		case ITEM_weapon_dagger_phasing:
		case ITEM_weapon_dagger_titanium:
		case ITEM_weapon_dagger_shard:
			// 전방 1칸 공격
			onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1, 0)));
			if (onceAttackSucess.OnceCheck()) {
				SOUND->Play("sfx_player_hit_ST");
				CAMERA->Shake(3, 5);
			}
			break;

			/* 레이피어 */
		case ITEM_weapon_rapier_blood:
			DATA->GainHp(4); // 흡혈
		case ITEM_weapon_rapier:
		case ITEM_weapon_rapier_glass:
		case ITEM_weapon_rapier_golden:
		case ITEM_weapon_rapier_obsidian:
		case ITEM_weapon_rapier_titanium:
			// 전방 2칸 공격 후 1칸 이동
			onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1, 0)));
			if (!onceAttackSucess.OnceCheck())
			{
				DamegeTarget(DirectionAxis(dir, 2, 0));
				if (onceAttackSucess.OnceCheck()) {
					SOUND->Play("sfx_player_hit_ST");
					CAMERA->Shake(5, 6);
				}
			}
			// 이동 검사후 이동
			if (objectm->CanMove(DirectionAxis(dir, 1, 0), this))
			{
				mMoveEvent.MoveOrder(dir);
				camera.MoveOrder(dir);
				onceFill = true;
			}
			return; // 이동 했으니 조건문 검사 오버헤드를 피함

			/* 롱소드 */
		case ITEM_weapon_longsword_blood:
			DATA->GainHp(4); // 흡혈
		case ITEM_weapon_longsword:
		case ITEM_weapon_longsword_glass:
		case ITEM_weapon_longsword_golden:
		case ITEM_weapon_longsword_obsidian:
		case ITEM_weapon_longsword_titaniun:
			if (objectm->GetObjectPtr(DirectionAxis(dir, 1, 0)))
			{
				onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 1, 0)));
				onceAttackSucess.Check(DamegeTarget(DirectionAxis(dir, 2, 0)));
				if (onceAttackSucess.OnceCheck()) {
					SOUND->Play("sfx_player_hit_ST");
					CAMERA->Shake(5, 6);
				}
			}
			break;
		}
	}
	if(!onceAttackSucess.OnceCheck())
	{
		if (objectm->CanMove(DirectionAxis(dir, 1, 0), this))
		{
			mMoveEvent.MoveOrder(dir);
			camera.MoveOrder(dir);
			onceFill = true;
			return; // 이동 했으니 조건문 검사 오버헤드를 피함
		}
	}


}
