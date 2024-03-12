#pragma once



enum class TextOption
{
	NONE,
	DISAPPEAR,
	HeartBeat,
	DamegeFont,
	Keep
};

struct TextEvent
{
	IDWriteTextLayout* text;
	NumberPrint num;
	bool numRender;
	wstring textsave;
	Vector2 position;
	float addition;
	ColorF::Enum color;
	TextOption option;
	float alpha;
	bool life;
	int timer;
	int ctimer;
	bool correction;
	float size;

	TextEvent(wstring text, float size, ColorF::Enum color = ColorF::White)
		: life(true)
		, alpha(1.0f)
		, ctimer(0)
		, size(size)
		, textsave(text)
		, numRender(false)
	{
		D2DRENDER->LayOutMake(&(this->text), text, size);
		this->color = color;
	}

	TextEvent(int size)
		: life(true)
		, alpha(1.0f)
		, ctimer(0)
		, size(size)
	{
		num.Init();
		numRender = true;
	}

	~TextEvent()
	{
		text->Release();
	}

	void SetEvent(Vector2 position, TextOption option = TextOption::NONE, float addition = 0, int timer = 90, bool correction = true) {
		this->option = option;
		this->position = position;
		this->addition = addition;
		this->timer = timer;
		this->correction = correction;
	}

	void SetText(wstring text, float size)
	{
		this->text->Release();
		D2DRENDER->LayOutMake(&(this->text), text, size);
	}

	void Render()
	{
		if (numRender)
		{
			num.Render(position, size, Vector2(30, 30), true);
			position.y -= 0.4f;
			num.alpha -= 0.02f;

			if (num.alpha < 0)
			{
				this->life = false;
			}
			return;
		}
		switch (option)
		{
		case TextOption::HeartBeat:
			this->text->Release();
			D2DRENDER->LayOutMake(&(this->text), textsave, size);
			size += addition;
			position -= addition * 6.0f;
			alpha -= 0.04;
			break;
		case TextOption::DISAPPEAR:
			alpha -= 0.01f;
			break;

		case TextOption::NONE:
			break;

		case TextOption::Keep:
			ctimer--;
			break;
		case TextOption::DamegeFont:
			position.y -= addition * 6.0f;
			alpha -= 0.02f;
			break;
		}

		if (correction)
		{
			if (life) {
				D2DRENDER->RenderText(CAMERA->CorrecteLocation(&position), text, color, alpha);
				ctimer++;
			}
		}
		else
		{
			if (life) {
				D2DRENDER->RenderText(position, text, color, alpha);
				ctimer++;
			}
		}

		position.y += addition;

		if (timer == ctimer) {
			this->life = false;
		}
	}
};

enum ItemQulity
{
	Qulity_Nomarl, // 일반
	Qulity_Masic,  // 고급
	Qulity_Rare,   // 희귀
	Qulity_Unique,  // 유일
	end_of_qulity
};

enum ItemPreffix
{
	preffix_Studded,     // 장식된 + 1
	preffix_Enveloped,   // 진보된 + 2
	preffix_Plated,      // 도금된 + 3
	preffix_Fortified,   //  요새 + 4
	preffix_Essences,    // 정수의 + 5

	preffix_Upgraded = 100,   // 강화된 + 1
	preffix_Heavy,     //  무거운 + 2
	preffix_Vicious,   //  잔인한 + 3
	preffix_terror,    //  공포의 + 4
	preffix_death,     // 죽음의 + 5
	end_of_preffix
};

enum ItemSuffix
{
	suffix_destroy, //(파괴) 공격력 + 10 %
	suffix_brave,   //(용기) 공격력 + 5 %, 방어력 5 %
	suffix_Life,    //(생명) 체력 + 5 %, 방어력 + 5 %
	suffix_Health,  //(건강) 체력 + 10 %
	end_of_suffix
};

enum ItemType
{
	// 브로드 소드
	ITEM_weapon_broadsword,
	ITEM_weapon_broadsword_blood,
	ITEM_weapon_broadsword_glass,
	ITEM_weapon_broadsword_golden,
	ITEM_weapon_broadsword_obsidian,
	ITEM_weapon_broadsword_titanium,
	// 단검
	ITEM_weapon_dagger,
	ITEM_weapon_dagger_blood,
	ITEM_weapon_dagger_glass,
	ITEM_weapon_dagger_golden,
	ITEM_weapon_dagger_phasing,
	ITEM_weapon_dagger_titanium,
	ITEM_weapon_dagger_shard, // 참고 : 유리 무기가 파괴되었을시 변경됨
	// 레이피어
	ITEM_weapon_rapier,
	ITEM_weapon_rapier_blood,
	ITEM_weapon_rapier_glass,
	ITEM_weapon_rapier_golden,
	ITEM_weapon_rapier_obsidian,
	ITEM_weapon_rapier_titanium,
	// 롱소드
	ITEM_weapon_longsword,
	ITEM_weapon_longsword_blood,
	ITEM_weapon_longsword_glass,
	ITEM_weapon_longsword_golden,
	ITEM_weapon_longsword_obsidian,
	ITEM_weapon_longsword_titaniun,
	// 삽
	ITEM_shovel_basic,
	// 방어구
	ITEM_armor_leather,
	ITEM_armor_chainmail,
	ITEM_armor_platemail,
	ITEM_armor_goldmail,
	// 횟불
	ITEM_torch_1,
	ITEM_torch_foresight,
	ITEM_torch_glass,
	//장비아이템 까지
	end_of_equal,

	// 비 장비아이템
	ITEM_coin,
	ITEM_daimond,
	ITEM_dirt_block,
	ITEM_coins_x2,
	ITEM_coins_x15,
	ITEM_misc_heart_container,
	ITEM_misc_heart_container_empty,
	ITEM_misc_heart_container_empty2,
	ITEM_misc_heart_container2,

	end_of_Do,
	// 능력치 계산
	ITEM_bomb,
	ITEM_CAL,
	end_of_item_type
};

class ItemInterface
{
public:
	int add; // 높은 증가
	Image* p;
	wstring ItemName;    // 아이템 이름
	ItemType itemType;
	ItemQulity qulity;  // 희귀도
	ItemPreffix prefix; // 접두사
	ItemSuffix suffix;  // 접미사
	int forged;         // 강화량

	string itemImage;
	string effect;
	string origin;
	Vector2 size;
	wstring desc;

	int price;     // 가격
	bool sell;     // 판매 가능 여부
	int amount;    // 수량
	int strength;  // 강화도

	int originPower;
	int originDefense;

	int power;   // 힘
	int defense; // 방어력

	bool isStackable; // 스택 가능 여부

	ItemInterface() = default;
	~ItemInterface() = default;

	virtual bool Meet() { return true; }
	virtual void Equal() {}
	virtual void UnEqual() {}
};

struct QuickSlotItem
{
	ItemInterface* p;
	bool in;
	QuickSlotItem()
		: p(nullptr)
		, in(false) {}
	~QuickSlotItem() {
		SAFE_DELETE(p);
	}
	void Push(ItemInterface* push)
	{
		if (in == false) {
			p = push;
			in = true;
		}
	}

	ItemInterface* Pull()
	{
		in = false;
		return p;
	}
};

inline bool nullBack(QuickSlotItem* p, QuickSlotItem* p2)
{
	return p->in > p2->in;
}


class Inventory : public SingletonBase<Inventory>
{
public:
	friend class SingletonBase<Inventory>;

	vector<ItemInterface*> m_items;
	vector<QuickSlotItem*> QucikSlot;

	Object* player;

	int bagSize;
	int QucikSlotSize;

	int index;
	int light;
	int currentItemIndex;

	Image* inventoryUI;
	Image* inven;
	Vector2 invenLocation;
	bool useInven;

	Image* trueComposite;
	Image* composite;
	Vector2 compositeLocation;
	bool usecomposite;

	ItemInterface* currentItem;

	Image* slot;
	Vector2 slotStartLocation;
	Vector2 slotGap;

	Vector2 slotSize;
	Vector2 itemInSlotSize;
	Vector2 zeroVector2;

	ItemInterface* weaphon;
	ItemInterface* armor;
	ItemInterface* shop;

	

	Inventory() {
		useInven = false;
		usecomposite = false;
		light = 0;

		QucikSlotSize = 5;
		currentItemIndex = 0;
		bagSize = 27;

		for (int i = 0; i < QucikSlotSize; ++i) {
			QucikSlot.push_back(new QuickSlotItem());
		}

		slotStartLocation = { 50, 200 };
		slotGap = { 0, 90 };
		slotSize = { 80, 80 };
		itemInSlotSize = { 50, 50 };
		zeroVector2 = { 0, 0 };

		currentItem = nullptr;

		weaphon = nullptr;
		armor = nullptr;
		shop = nullptr;

		index = -1;
	}

	void Init()
	{
		slot = IMAGE->FindImage("slot");
		inventoryUI = IMAGE->FindImage("inven");
		inven = IMAGE->FindImage("saveinven");
		composite = IMAGE->FindImage("composite");
		trueComposite = IMAGE->FindImage("savesave");
		compositeLocation = { 140, 245 };
		invenLocation = { 140, 205 };
	}

	void Render()
	{
		IMAGE->FindImage("hud_attack")->SetSize(slotSize);
		IMAGE->FindImage("hud_attack")->Render(Vector2(50, 100));
		IMAGE->FindImage("hud_body")->SetSize(slotSize);
		IMAGE->FindImage("hud_body")->Render(Vector2(140, 100));
		IMAGE->FindImage("hud_shov")->SetSize(slotSize);
		IMAGE->FindImage("hud_shov")->Render(Vector2(230, 100));

		if (weaphon != nullptr) {
			weaphon->p->SetSize(itemInSlotSize);
			weaphon->p->Render(Vector2(65, 120), zeroVector2);
		}
		if (armor != nullptr) {
			armor->p->SetSize(itemInSlotSize);
			armor->p->Render(Vector2(155, 120), zeroVector2);
		}
		if (shop != nullptr) {
			shop->p->SetSize(itemInSlotSize);
			shop->p->Render(Vector2(245, 120), zeroVector2);
		}

		if (!useInven)
		{
			inventoryUI->SetSize(Vector2(100, 30));
			inventoryUI->Render(invenLocation);
		}
		if (!usecomposite)
		{
			composite->SetSize(Vector2(100, 30));
			composite->Render(compositeLocation);
		}

		if (KEY->IsOnceKeyDown(VK_RBUTTON)) 
		{
			QuickEqual_or_PopbackToQuickBar();
			QuickUnEqual(FloatRect(65, 120, 145, 200), &weaphon, &player->currentItem);
			QuickUnEqual(FloatRect(155, 120, 235, 200), &armor, &player->currentArmor);
			QuickUnEqual(FloatRect(245, 120, 325, 200), &shop, &player->currentShov);
		}

		if (KEY->IsOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(_ptMouse, FloatRect(invenLocation.x, invenLocation.y, invenLocation.x + 100, invenLocation.y + 30)))
			{// 인벤토리
				useInven = true;
				compositeLocation.y = invenLocation.y + 170;
			}
			if (!(PtInRect(_ptMouse, FloatRect(0, 0, 450, 300))))
			{
				useInven = false;
				usecomposite = false;
				currentItem = nullptr;
				compositeLocation.y = invenLocation.y + 40;

			}// 합성
			if (PtInRect(_ptMouse, FloatRect(compositeLocation.x, compositeLocation.y, compositeLocation.x + 100, compositeLocation.y + 30)))
			{
				usecomposite = true;
			}

			if (currentItem != nullptr)
			{
				for (int i = 0; i < QucikSlotSize; ++i)
				{
					if (PtInRect(_ptMouse, FloatRect(slotStartLocation.x, slotStartLocation.y + i * slotGap.y,
						slotStartLocation.x + slotSize.x, slotStartLocation.y + i * slotGap.y + slotSize.y)))
					{
						ItemInterface* temp = QucikSlot[i]->p;
						QucikSlot[i]->p = currentItem;
						m_items.push_back(temp);
						currentItem = nullptr;
						m_items.erase(m_items.begin() + currentItemIndex);
						currentItemIndex = -1;
						break;
					}
				}

			}
		}

		if (KEY->IsStayKeyDown(VK_ESCAPE))
		{
			currentItem = nullptr;
		}

		if (usecomposite)
		{
			trueComposite->SetSize(Vector2(200,100));
			trueComposite->Render(compositeLocation.x, compositeLocation.y);
		}

		if (useInven)
		{
			inven->SetSize(Vector2(450, 170));
			inven->Render(Vector2(invenLocation.x, invenLocation.y));

			int y = 0;
			int x = 0;

			// 인벤토리 출력
			for (int i = 0; i < m_items.size(); ++i)
			{
				if (m_items[i]) {
					m_items[i]->p->SetSize(Vector2(50, 50));
					m_items[i]->p->Render(Vector2(invenLocation.x + x * 50, invenLocation.y + y * 50), zeroVector2);
					x++;
				}
				if (x > 9)
				{
					x = 0;
					y++;
				}
			}

			y = 0;
			x = 0;

			if (KEY->IsOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 0; i < m_items.size(); ++i)
				{
					if (PtInRect(_ptMouse, FloatRect(invenLocation.x + x * 50, invenLocation.y + y * 50, invenLocation.x + x * 50 + 50, invenLocation.y + y * 50 + 50)))
					{
						currentItem = m_items[i];
						currentItemIndex = i;
						break;
					}
					x++;
					if (x > 9) {
						x = 0;
						y++;
					}
				}
			}

			y = 0;
			x = 0;

			if (KEY->IsOnceKeyDown(VK_RBUTTON))
			{
				for (int i = 0; i < m_items.size(); ++i) {
					if (PtInRect(_ptMouse, FloatRect(invenLocation.x + x * 50, invenLocation.y + y * 50, invenLocation.x + x * 50 + 50, invenLocation.y + y * 50 + 50)))
					{
						SAFE_DELETE(m_items[i]);
						m_items.erase(m_items.begin() + i);
						break;
					}
					x++;
					if (x > 9) {
						x = 0;
						y++;
					}
				}
			}
		}

		if (KEY->IsOnceKeyDown('1'))
		{
			QuickEqual_or_PopbackToQuickBar(0);
		}
		if (KEY->IsOnceKeyDown('2'))
		{
			QuickEqual_or_PopbackToQuickBar(1);
		}
		if (KEY->IsOnceKeyDown('3'))
		{
			QuickEqual_or_PopbackToQuickBar(2);
		}
		if (KEY->IsOnceKeyDown('4'))
		{
			QuickEqual_or_PopbackToQuickBar(3);
		}
		if (KEY->IsOnceKeyDown('5'))
		{
			QuickEqual_or_PopbackToQuickBar(4);
		}

		for (int i = 0; i < QucikSlotSize; ++i) {
			slot->SetSize(slotSize);
			slot->Render(Vector2(slotStartLocation.x, slotStartLocation.y + i * slotGap.y));
			if (QucikSlot[i]->p) {
				QucikSlot[i]->p->p->SetSize(Vector2(itemInSlotSize));
				QucikSlot[i]->p->p->Render(Vector2(slotStartLocation.x - 15, slotStartLocation.y + i * slotGap.y) + 25, zeroVector2);
			}
		}

		if (currentItem != nullptr) {
			currentItem->p->SetAlpha(0.6f);
			currentItem->p->SetSize(Vector2(50,50));
			currentItem->p->Render(_ptMouse + 20,zeroVector2);
		}

	}// 함수의 끄읏

	void QuickEqual_or_PopbackToQuickBar()
	{
		for (int i = 0; i < QucikSlotSize; ++i) 
		{
			if (PtInRect(_ptMouse, FloatRect(slotStartLocation.x, slotStartLocation.y + i * slotGap.y,
				slotStartLocation.x + slotSize.x, slotStartLocation.y + i * slotGap.y + slotSize.y)))
			{
				if (QucikSlot[i]->p != nullptr)
				{
					ItemInterface* p = nullptr;
					switch (QucikSlot[i]->p->itemType)
					{
						// 브로드 소드
					case ITEM_weapon_broadsword:
					case ITEM_weapon_broadsword_blood:
					case ITEM_weapon_broadsword_glass:
					case ITEM_weapon_broadsword_golden:
					case ITEM_weapon_broadsword_obsidian:
					case ITEM_weapon_broadsword_titanium:
						// 단검
					case ITEM_weapon_dagger:
					case ITEM_weapon_dagger_blood:
					case ITEM_weapon_dagger_glass:
					case ITEM_weapon_dagger_golden:
					case ITEM_weapon_dagger_phasing:
					case ITEM_weapon_dagger_titanium:
					case ITEM_weapon_dagger_shard:
						// 레이피어
					case ITEM_weapon_rapier:
					case ITEM_weapon_rapier_blood:
					case ITEM_weapon_rapier_glass:
					case ITEM_weapon_rapier_golden:
					case ITEM_weapon_rapier_obsidian:
					case ITEM_weapon_rapier_titanium:
						// 롱소드
					case ITEM_weapon_longsword:
					case ITEM_weapon_longsword_blood:
					case ITEM_weapon_longsword_glass:
					case ITEM_weapon_longsword_golden:
					case ITEM_weapon_longsword_obsidian:
					case ITEM_weapon_longsword_titaniun:
						m_items.push_back(new ItemInterface(*QucikSlot[i]->p));
						weaphon = nullptr;
						player->currentItem = nullptr;
						QucikSlot[i]->p = nullptr;
						QucikSlot[i]->in = false;
						break;
						////////////////////////////// 무기
					case ITEM_shovel_basic:
						m_items.push_back(new ItemInterface(*QucikSlot[i]->p));
						shop = nullptr;
						player->currentShov = nullptr;
						QucikSlot[i]->p = nullptr;
						QucikSlot[i]->in = false;
						break;
						////////////////////////////// 삽
					case ITEM_armor_leather:
					case ITEM_armor_chainmail:
					case ITEM_armor_platemail:
					case ITEM_armor_goldmail:
						m_items.push_back(new ItemInterface(*QucikSlot[i]->p));
						player->torso.SetDrawLocation(0);
						armor = nullptr;
						player->currentArmor = nullptr;
						QucikSlot[i]->p = nullptr;
						QucikSlot[i]->in = false;
						break;
						///////////////////////////// 방어구
					}
				}
				break;
			}
		}
		sort(QucikSlot.begin(), QucikSlot.end(), nullBack);
	}

	void QuickEqual_or_PopbackToQuickBar(int index)
	{
		if (index > 4) return; // 예외 :: 인덱스 초과

		if (QucikSlot[index]->p != nullptr)
		{
			ItemInterface* p = nullptr;
			switch (QucikSlot[index]->p->itemType)
			{
				// 브로드 소드
			case ITEM_weapon_broadsword:
			case ITEM_weapon_broadsword_blood:
			case ITEM_weapon_broadsword_glass:
			case ITEM_weapon_broadsword_golden:
			case ITEM_weapon_broadsword_obsidian:
			case ITEM_weapon_broadsword_titanium:
				// 단검
			case ITEM_weapon_dagger:
			case ITEM_weapon_dagger_blood:
			case ITEM_weapon_dagger_glass:
			case ITEM_weapon_dagger_golden:
			case ITEM_weapon_dagger_phasing:
			case ITEM_weapon_dagger_titanium:
			case ITEM_weapon_dagger_shard:
				// 레이피어
			case ITEM_weapon_rapier:
			case ITEM_weapon_rapier_blood:
			case ITEM_weapon_rapier_glass:
			case ITEM_weapon_rapier_golden:
			case ITEM_weapon_rapier_obsidian:
			case ITEM_weapon_rapier_titanium:
				// 롱소드
			case ITEM_weapon_longsword:
			case ITEM_weapon_longsword_blood:
			case ITEM_weapon_longsword_glass:
			case ITEM_weapon_longsword_golden:
			case ITEM_weapon_longsword_obsidian:
			case ITEM_weapon_longsword_titaniun:
				p = weaphon;
				weaphon = QucikSlot[index]->p;
				player->currentItem = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
				////////////////////////////// 무기
			case ITEM_shovel_basic:
				p = shop;
				shop = QucikSlot[index]->p;
				player->currentShov = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
				////////////////////////////// 삽
			case ITEM_armor_leather:
				player->torso.SetDrawLocation(1);
				p = armor;
				armor = QucikSlot[index]->p;
				player->currentArmor = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
			case ITEM_armor_chainmail:
				player->torso.SetDrawLocation(2);
				p = armor;
				armor = QucikSlot[index]->p;
				player->currentArmor = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
			case ITEM_armor_platemail:
				player->torso.SetDrawLocation(3);
				p = armor;
				armor = QucikSlot[index]->p;
				player->currentArmor = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
			case ITEM_armor_goldmail:
				player->torso.SetDrawLocation(4);
				p = armor;
				armor = QucikSlot[index]->p;
				player->currentArmor = QucikSlot[index]->p;
				QucikSlot[index]->p = p;
				break;
				///////////////////////////// 방어구
			}
		}

		sort(QucikSlot.begin(), QucikSlot.end(), nullBack);
	}


	void QuickUnEqual(FloatRect barLocation, ItemInterface ** null1, ItemInterface ** null2)
	{
		if (PtInRect(_ptMouse, barLocation))
		{
			if (null1 != nullptr && null2 != nullptr)
			{
				for (int i = 0; i < QucikSlotSize; ++i) 
				{
					if (QucikSlot[i]->p == nullptr) {
						QucikSlot[i]->in = false;
						QucikSlot[i]->Push((*null2));
						(*null1) = nullptr;
						(*null2) = nullptr;
						break;
					}
				}
			}
		}
		sort(QucikSlot.begin(), QucikSlot.end(), nullBack);
	}


	// 새로 입수한 아이템 p 에 매칭하는 빈슬롯이 있을 경우, 바로 장착.
	void InsertEmptyMainSlot(ItemInterface * p)
	{
		bool inthethesea = false;
		for (int i = 0; i < QucikSlot.size(); ++i) 
		{ // 빈 공간이 있다면 아이템 삽입.
			if (QucikSlot[i]->in) continue; // 예외 :: already have
			ExchangeItemSlot(p, i);
			ItemEqual(p, i);
			inthethesea = true;
			break;
		}
		if(!inthethesea)
		m_items.push_back(p);
	}

	void GetPlayer(Object * p)
	{
		this->player = p;
	}

	// 아이템 추가
	bool AddItem(ItemInterface * p) {
		if (bagSize > m_items.size()) { // 예외 :: vector out of index
			m_items.push_back(p);
			bagSize++;
			return true;
		}
		return false;
	}


	void ItemEqual(ItemInterface * item_, int index = -2)
	{
		switch (item_->itemType)
		{
			// 브로드 소드
		case ITEM_weapon_broadsword:
		case ITEM_weapon_broadsword_blood:
		case ITEM_weapon_broadsword_glass:
		case ITEM_weapon_broadsword_golden:
		case ITEM_weapon_broadsword_obsidian:
		case ITEM_weapon_broadsword_titanium:
			// 단검
		case ITEM_weapon_dagger:
		case ITEM_weapon_dagger_blood:
		case ITEM_weapon_dagger_glass:
		case ITEM_weapon_dagger_golden:
		case ITEM_weapon_dagger_phasing:
		case ITEM_weapon_dagger_titanium:
		case ITEM_weapon_dagger_shard:
			// 레이피어
		case ITEM_weapon_rapier:
		case ITEM_weapon_rapier_blood:
		case ITEM_weapon_rapier_glass:
		case ITEM_weapon_rapier_golden:
		case ITEM_weapon_rapier_obsidian:
		case ITEM_weapon_rapier_titanium:
			// 롱소드
		case ITEM_weapon_longsword:
		case ITEM_weapon_longsword_blood:
		case ITEM_weapon_longsword_glass:
		case ITEM_weapon_longsword_golden:
		case ITEM_weapon_longsword_obsidian:
		case ITEM_weapon_longsword_titaniun:
			if (player->currentItem == nullptr) {
				player->currentItem = item_;
				this->weaphon = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;
			}

			break;
			////////////////////////////// 무기
		case ITEM_shovel_basic:
			if (player->currentShov == nullptr) {
				player->currentShov = item_;
				this->shop = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;

			}
			break;
			////////////////////////////// 삽
		case ITEM_armor_leather:
			if (player->currentArmor == nullptr)
			{
				player->currentArmor = item_;
				player->torso.SetDrawLocation(1);
				this->armor = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;

			}
			break;
		case ITEM_armor_chainmail:
			if (player->currentArmor == nullptr)
			{
				player->currentArmor = item_;
				player->torso.SetDrawLocation(2);
				this->armor = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;
			}
			break;
		case ITEM_armor_platemail:
			if (player->currentArmor == nullptr)
			{
				player->currentArmor = item_;
				player->torso.SetDrawLocation(3);
				this->armor = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;
			}
			break;
		case ITEM_armor_goldmail:
			if (player->currentArmor == nullptr)
			{
				player->currentArmor = item_;
				player->torso.SetDrawLocation(4);
				this->armor = item_;
				QucikSlot[index]->p = nullptr;
				QucikSlot[index]->in = false;
			}
			break;
			///////////////////////////// 방어구
		}

	}

	// 아이템 변경
	void ExchangeItemSlot(ItemInterface * slotNum, int num)
	{
		if (num > 4) return; // 예외 :: vector out of index
		ItemInterface* tempSlot = nullptr;
		if (slotNum == nullptr)
		{
			tempSlot = slotNum;
			slotNum = QucikSlot[num]->p;
			QucikSlot[num]->in = false;
			QucikSlot[num]->Push(tempSlot);
			return;
		}
		switch (slotNum->itemType)
		{
			// 브로드 소드
		case ITEM_weapon_broadsword:
		case ITEM_weapon_broadsword_blood:
		case ITEM_weapon_broadsword_glass:
		case ITEM_weapon_broadsword_golden:
		case ITEM_weapon_broadsword_obsidian:
		case ITEM_weapon_broadsword_titanium:
			// 단검
		case ITEM_weapon_dagger:
		case ITEM_weapon_dagger_blood:
		case ITEM_weapon_dagger_glass:
		case ITEM_weapon_dagger_golden:
		case ITEM_weapon_dagger_phasing:
		case ITEM_weapon_dagger_titanium:
		case ITEM_weapon_dagger_shard:
			// 레이피어
		case ITEM_weapon_rapier:
		case ITEM_weapon_rapier_blood:
		case ITEM_weapon_rapier_glass:
		case ITEM_weapon_rapier_golden:
		case ITEM_weapon_rapier_obsidian:
		case ITEM_weapon_rapier_titanium:
			// 롱소드
		case ITEM_weapon_longsword:
		case ITEM_weapon_longsword_blood:
		case ITEM_weapon_longsword_glass:
		case ITEM_weapon_longsword_golden:
		case ITEM_weapon_longsword_obsidian:
		case ITEM_weapon_longsword_titaniun:
			tempSlot = slotNum;
			slotNum = QucikSlot[num]->Pull();
			QucikSlot[num]->Push(tempSlot);
			break;
			////////////////////////////// 무기
		case ITEM_shovel_basic:
			tempSlot = slotNum;
			slotNum = QucikSlot[num]->Pull();
			QucikSlot[num]->Push(tempSlot);
			break;
			////////////////////////////// 삽
		case ITEM_armor_leather:
		case ITEM_armor_chainmail:
		case ITEM_armor_platemail:
		case ITEM_armor_goldmail:
			tempSlot = slotNum;
			slotNum = QucikSlot[num]->Pull();
			QucikSlot[num]->Push(tempSlot);
			break;
			///////////////////////////// 방어구
		}
	}

	~Inventory()
	{
		for (int i = 0; i < m_items.size(); ++i) {
			SAFE_DELETE(m_items[i]);
		}
	}

};

#define INVEN Inventory::Get()



class Item : public ItemInterface
{
public:
	Item() {}

	void SetItemStatus(ItemType type);
	virtual string GetImageNaem() const { if (p != nullptr) { return p->GetKey(); } return ""; }

	Item(ItemType type, int add = 0, int amount = 1, bool stackable = false, int price = 0, bool sell = false)
	{
		Image* p;
		this->add = add;
		qulity = end_of_qulity;
		prefix = end_of_preffix;
		suffix = end_of_suffix;
		forged = 0;
		desc = L"";
		this->isStackable = stackable;
		originPower = 0;
		originDefense = 0;

		power = 0;   // 힘
		defense = 0; // 방
		this->amount = amount;
		SetItemStatus(type);

		size = { TILESIZE_X, TILESIZE_Y };

		this->sell = sell;
		this->price = price;
	}

	virtual bool Meet() {
		if (sell) {
			if (DATA->coin >= price) {
				DATA->coin -= price;
				INVEN->m_items.push_back(this);
				return true;
			}
		}
		else {
			if (this->itemType == ITEM_coin) {
				SOUND->Play("sfx_pickup_gold_01");
				DATA->coin += amount;
			}
			else if (itemType == ITEM_daimond) {
				SOUND->Play("sfx_pickup_diamond");
				DATA->daimond += amount;
			}
			else if (itemType == ITEM_misc_heart_container) {
				DATA->maxhp += 10;
				DATA->hp += 10;
			}
			else if (itemType == ITEM_misc_heart_container2) {
				DATA->maxhp += 20;
				DATA->hp += 20;
			}
			else if (itemType == ITEM_misc_heart_container_empty) {
				DATA->maxhp += 10;
			}
			else if (itemType == ITEM_misc_heart_container_empty2) {
				DATA->maxhp += 20;
			}
			else {
				if (isStackable)
				{
					for (int i = 0; i < INVEN->m_items.size(); ++i)
					{
						if (INVEN->m_items[i] != nullptr)
						{
							if (this->itemType == INVEN->m_items[i]->itemType)
							{
								INVEN->m_items[i]->amount++;
								return true;
							}
						}
					}
					INVEN->AddItem(this);
				}
				else
				{
					INVEN->AddItem(this);

				}

			}
			return true;
		}
		return false;
	}



	~Item() = default;
};
