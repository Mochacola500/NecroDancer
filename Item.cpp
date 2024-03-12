#include "stdafx.h"
#include "Item.h"

void SetSuffix(wstring& name, ItemSuffix suffix, float& spp,
	float& sdp)
{
	wstring newName;
	switch (suffix)
	{
	case suffix_destroy:
		newName = name + L" (�ı�)";
		name = newName;
		spp += 10.f;
		return;
	case suffix_brave:
		newName = name + L" (���)";
		name = newName;
		spp += 5.f;
		sdp += 5.f;
		return;
	case suffix_Life:
		newName = name + L" (����)";
		name = newName;
		return;
	case suffix_Health:
		newName = name + L" (�ǰ�)";
		name = newName;
		sdp += 10.f;
		return;
	}
}

void SetStrength(wstring& name, int& add)
{
	wstring newName;
	int forged = rand() % (100 - add);

	if (forged < 20)
	{
		int addp = (rand() % 100) + add + 1;
		addp /= 10;
		add = addp;
		if (addp > 0)
		{
			newName = name + L" + " + to_wstring(addp);
			name = newName;
		}
	}
}

void SetPrefix(wstring& name, ItemPreffix prefix, int& pp, int& pd)
{
	wstring newName;
	switch (prefix)
	{
		case preffix_Studded:
			newName = L"��ĵ� " + name;
			name = newName;
			pd = 1;
			return;
		case preffix_Enveloped:
			newName = L"������ " + name;
			name = newName;
			pd = 2;
			return;
		case preffix_Plated:
			newName = L"�Ǳ��� " + name;
			name = newName;
			pd = 3;
			return;
		case preffix_Fortified:
			newName = L"����� " + name;
			name = newName;
			pd = 4;
			return;
		case preffix_Essences:
			newName = L"������ " + name;
			name = newName;
			pd = 5;
			return;
		case preffix_Upgraded:
			newName = L"��ȭ�� " + name;
			name = newName;
			pp = 1;
			return;
		case preffix_Heavy:
			newName = L"���ſ� " + name;
			name = newName;
			pp = 2;
			return;
		case preffix_Vicious:
			newName = L"������ " + name;
			name = newName;
			pp = 3;
			return;
		case preffix_terror:
			newName = L"������ " + name;
			name = newName;
			pp = 4;
			return;
		case preffix_death:
			newName = L"������ " + name;
			name = newName;
			pp = 5;
			return;
	}
}

void SetItemQulity(wstring& name, ItemQulity qulity, float& spp, float& spd)
{
	wstring newName;
	switch (qulity)
	{
	case Qulity_Nomarl:
		newName = name + L" �Ϲ� ";
		return;
	case Qulity_Masic:
		newName = name + L" ��� ";
		spp += 4.f;
		spd += 4.f;
		return;
	case Qulity_Rare:
		newName = name + L" ��� ";
		spp += 8.f;
		spd += 8.f;
		return;
	case Qulity_Unique:
		newName = name + L" ���� ";
		spp += 12.f;
		spd += 12.f;
		return;
	default:
		break;
	}
}


ItemQulity SetRare(int add)
{
	int rare = rand() % (100 - add);
	if (rare < 3) return Qulity_Unique;
	else if (rare < 8) return Qulity_Rare;
	else if (rare < 19) return Qulity_Masic;
	else return Qulity_Nomarl;
}

ItemPreffix SetPrefix(int add)
{
	int preffix = rand() % (100 - add);

	if (preffix < 2)       return 	preffix_Studded;
	else if (preffix < 4)  return	preffix_Enveloped;
	else if (preffix < 6)  return	preffix_Plated;
	else if (preffix < 8)  return	preffix_Fortified;
	else if (preffix < 10) return	preffix_Essences;
	else if (preffix < 12) return   preffix_Upgraded;
	else if (preffix < 14) return	preffix_Heavy;
	else if (preffix < 16) return	preffix_Vicious;
	else if (preffix < 18) return	preffix_terror;
	else if (preffix < 20) return	preffix_death;

	return end_of_preffix;			
}

ItemSuffix SetSuffix(int add)
{
	int suffix = rand() % (100 - add);

	if (suffix < 2)       return suffix_destroy;
	else if (suffix < 4)  return	suffix_brave;
	else if (suffix < 6)  return	suffix_Life;
	else if (suffix < 8)  return	suffix_Health;

	return end_of_suffix;
}


void SetItemAttribute(ItemInterface* p)
{
	// ��� �ӽ� ����
	int prefixPower = 0;
	int prefixDefense = 0;
	float suffixPowerPer = 0.f;
	float suffixDefensePer = 0.f;

	// �ΰ� �ɷ�ġ
	SetStrength(p->ItemName, p->add);
	SetPrefix(p->ItemName, p->prefix, prefixPower, prefixDefense);
	SetItemQulity(p->ItemName, p->qulity, suffixPowerPer, suffixDefensePer);
	SetSuffix(p->ItemName, p->suffix, suffixPowerPer, suffixDefensePer);

	// �ɷ�ġ ���
	int addPower = p->originPower + prefixPower;
	p->power = addPower + p->add + addPower * ((suffixPowerPer) / 100.f);
	int addDefense = p->originDefense + prefixDefense;
	p->defense = addDefense + p->add + addDefense * ((suffixDefensePer) / 100.f);
}

void Item::SetItemStatus(ItemType type)
{
	int value;
	itemType = type;
	switch (type)
	{
	//////////////////////////////////////////// ���
	case ITEM_coin:
		itemImage = "resource_coin";
		origin = "resource_coin";
		effect = "resource_coin";
		value = amount;
		if (value > 9) value = 10;
		if (value < 0) value = 0;
		this->itemImage = itemImage + to_string(value);
		ItemName = L"Ȳ�� x " + to_wstring(amount);
		break;
	case ITEM_daimond:
		itemImage = "resource_diamond";
		origin = "resource_diamond";
		effect = "resource_diamond";
		value = amount;
		if (value > 4) value = 4;
		if (value < 0) value = 0;
		this->itemImage = itemImage + to_string(value);
		ItemName = L"���̾Ƹ�� x " + to_wstring(amount);
		break;
	///////////////////////////////////////////// �ڿ�

	///////////////////////////////////////////// ����
	case ITEM_weapon_dagger:
		ItemName = L"�ܰ�"; // �ܰ�
		itemImage = "weapon_dagger";
		origin = "weapon_dagger";
		effect = "swipe_dagger";
		power = originPower = 10;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_blood:
		ItemName = L"�ܰ� - ��";
		itemImage = "weapon_dagger_blood";
		origin = "weapon_dagger_blood";
		effect = "swipe_dagger_blood";
		power = originPower = 10;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_glass:
		ItemName = L"�ܰ� - ����";
		itemImage = "weapon_dagger_glass";
		origin = "weapon_dagger_glass";
		effect = "swipe_dagger_glass";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_golden:
		ItemName = L"�ܰ� - Ȳ��";
		itemImage = "weapon_dagger_golden";
		origin = "weapon_dagger_golden";
		effect = "swipe_dagger_gold";
		power = originPower = 5;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_phasing:
		ItemName = L"�ܰ� - ����";
		itemImage = "weapon_dagger_phasing";
		origin = "weapon_dagger_phasing";
		effect = "swipe_dagger";
		power = originPower = 8;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_titanium:
		ItemName = L"�ܰ� - ƼŸ��";
		itemImage = "weapon_dagger_titanium";
		origin = "weapon_dagger_titanium";
		effect = "swipe_dagger_titanuim";
		power = originPower = 10;
		goto LABEL_CAL;
	case ITEM_weapon_dagger_shard:
		ItemName = L"�μ��� ����";
		itemImage = "weapon_dagger_shard";
		origin = "weapon_dagger_shard";
		effect = "swipe_dagger";
		power = originPower = 4;
		break;        // ���� : ����� ������ �ı��� ����. �ΰ� ȿ�� X
	case ITEM_weapon_broadsword: // ��ε�ҵ�
		ItemName = L"��ε� �ҵ�";
		itemImage = "weapon_broadsword";
		origin = "weapon_broadsword";
		effect = "swipe_broadsword";
		power = originPower = 10 ;
		goto LABEL_CAL;
	case ITEM_weapon_broadsword_blood:
		ItemName = L"��ε� �ҵ� - ��";
		itemImage = "weapon_broadsword_blood";
		origin = "weapon_broadsword_blood";
		effect = "swipe_broadsword_blood";
		power = originPower = 10;
		goto LABEL_CAL;
	case ITEM_weapon_broadsword_glass:
		ItemName = L"��ε� �ҵ� - ����";
		itemImage = "weapon_broadsword_glass";
		origin = "weapon_broadsword_glass";
		effect = "swipe_broadsword_glass";
		power = originPower = 40;
		goto LABEL_CAL;
	case ITEM_weapon_broadsword_golden:
		ItemName = L"��ε� �ҵ� - Ȳ��";
		itemImage = "weapon_broadsword_golden";
		origin = "weapon_broadsword_golden";
		effect = "swipe_broadsword_gold";
		power = originPower = 10;
		goto LABEL_CAL;
	case ITEM_weapon_broadsword_obsidian:
		ItemName = L"��ε� �ҵ� - ��伮";
		itemImage = "weapon_broadsword_obsidian";
		origin = "weapon_broadsword_obsidian";
		effect = "swipe_broadsword_obsidian";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_broadsword_titanium:
		ItemName = L"��ε� �ҵ� - ƼŸ��";
		itemImage = "weapon_broadsword_titanium";
		origin = "weapon_broadsword_titanium";
		effect = "swipe_broadsword_titanium";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_rapier: // ���� �Ǿ�
		ItemName = L"���� �Ǿ�";
		itemImage = "weapon_rapier";
		origin = "weapon_rapier";
		effect = "swipe_rapier";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_rapier_blood:
		ItemName = L"���� �Ǿ� - ��";
		itemImage = "weapon_rapier_blood";
		origin = "weapon_rapier_blood";
		effect = "swipe_rapier_blood";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_rapier_glass:
		ItemName = L"���� �Ǿ� - ����";
		itemImage = "weapon_rapier_glass";
		origin = "weapon_rapier_glass";
		effect = "swipe_rapier_glass";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_rapier_golden:
		ItemName = L"���� �Ǿ� - Ȳ��";
		itemImage = "weapon_rapier_golden";
		origin = "weapon_rapier_golden";
		effect = "swipe_rapier_gold";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_rapier_obsidian:
		ItemName = L"���� �Ǿ� - ��伮";
		itemImage = "weapon_rapier_obsidian";
		origin = "weapon_rapier_obsidian";
		effect = "swipe_rapier_obsidian";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_rapier_titanium:
		ItemName = L"���� �Ǿ� - ƼŸ��";
		itemImage = "weapon_rapier_titanium";
		origin = "weapon_rapier_titanium";
		effect = "swipe_rapier_titanium";
		power = originPower = 15;
		goto LABEL_CAL;
	case ITEM_weapon_longsword:
		ItemName = L"�ռҵ�"; // �ռҵ�
		itemImage = "weapon_longsword";
		origin = "weapon_longsword";
		effect = "swipe_longsword";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_longsword_blood:
		ItemName = L"�ռҵ� - ��";
		itemImage = "weapon_longsword_blood";
		origin = "weapon_longsword_blood";
		effect = "swipe_longsword_blood";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_longsword_glass:
		ItemName = L"�ռҵ� - ����";
		itemImage = "weapon_longsword_glass";
		origin = "weapon_longsword_glass";
		effect = "swipe_longsword_glass";
		power = originPower = 80;
		goto LABEL_CAL;
	case ITEM_weapon_longsword_golden:
		ItemName = L"�ռҵ� - Ȳ��";
		itemImage = "weapon_longsword_golden";
		origin = "weapon_longsword_golden";
		effect = "swipe_longsword_gold";
		power = originPower = 20;
		goto LABEL_CAL;
	case ITEM_weapon_longsword_obsidian:
		ItemName = L"�ռҵ� - ��伮";
		itemImage = "weapon_longsword_obsidian";
		origin = "weapon_longsword_obsidian";
		effect = "swipe_longsword_obsidian";
		power = originPower = 40;
		goto LABEL_CAL;
	case ITEM_weapon_longsword_titaniun:
		ItemName = L"�ռҵ� - ƼŸ��";
		itemImage = "weapon_longsword_titanium";
		origin = "weapon_longsword_titanium";
		effect = "swipe_longsword_titanium";
		power = originPower = 40;
		goto LABEL_CAL;
	/////////////////////////////////////////// ��
	case ITEM_shovel_basic:
		ItemName = L"��";
		itemImage = "shovel_basic";
		origin = "shovel_basic";
		effect = "shovel_basic";
		power = originPower = 1;
		break;
	/////////////////////////////////////////// ��
	case ITEM_armor_leather:
		ItemName = L"���� ����";
		itemImage = "armor_leather";
		origin = "armor_leather";
		effect = "armor_leather";
		defense = originDefense = 1;
		goto LABEL_CAL;
	case ITEM_armor_chainmail:
		ItemName = L"�罽 ����";
		itemImage = "armor_chainmail";
		origin = "armor_chainmail";
		effect = "armor_chainmail";
		defense = originDefense = 2;
		goto LABEL_CAL;
	case ITEM_armor_platemail:
		ItemName = L"�ݼ� ����";
		itemImage = "armor_platemail";
		origin = "armor_platemail";
		effect = "armor_platemail";
		defense = originDefense = 3;
		goto LABEL_CAL;
	case ITEM_armor_goldmail:
		ItemName = L"��ȭ ����";
		itemImage = "armor_goldmail";
		origin = "armor_goldmail";
		effect = "armor_goldmail";
		defense = originDefense = 4;
		goto LABEL_CAL;
	/////////////////////////////////////// �Һ� ������
	case ITEM_coins_x2:
		ItemName = L"���� 2��";
		itemImage = "coins_x2";
		origin = "coins_x2";
		effect = "coins_x2";
		break;
	case ITEM_coins_x15:
		ItemName = L"���� 1.5��";
		itemImage = "coins_x15";
		origin = "coins_x15";
		effect = "coins_x15";
		break;
	case ITEM_CAL:
	LABEL_CAL:
		this->qulity = SetRare(add);
		this->prefix = SetPrefix(add);
		this->suffix = SetSuffix(add);
		SetItemAttribute(this);
		break;
	case ITEM_misc_heart_container:
		ItemName = L"��Ʈ + 1";
		itemImage = "misc_heart_container";
		origin = "misc_heart_container";
		effect = "misc_heart_container";
		break;
	case ITEM_misc_heart_container_empty:
		ItemName = L"�� ��Ʈ + 1";
		itemImage = "misc_heart_container_empty";
		origin = "misc_heart_container_empty";
		effect = "misc_heart_container_empty";
		break;
	case ITEM_misc_heart_container_empty2:
		ItemName = L"�� ��Ʈ + 2";
		itemImage = "misc_heart_container_empty2";
		origin = "misc_heart_container_empty2";
		effect = "misc_heart_container_empty2";
		break;
	case ITEM_misc_heart_container2:
		ItemName = L"��Ʈ + 2";
		itemImage = "misc_heart_container2";
		origin = "misc_heart_container2";
		effect = "misc_heart_container2";
		break;
	////////////////////////////////////// Ƚ��
	case ITEM_torch_1:
		ItemName = L"Ƚ��";
		itemImage = "torch_1";
		origin = "torch_1";
		effect = "torch_1";
		this->power = 1;
		break;
	case ITEM_torch_foresight:
		ItemName = L"�������� Ƚ��";
		itemImage = "torch_foresight";
		origin = "torch_foresight";
		effect = "torch_foresight";
		this->power = 2;
		break;
	case ITEM_torch_glass:
		ItemName = L"���� Ƚ��";
		itemImage = "torch_glass";
		origin = "torch_glass";
		effect = "torch_glass";
		this->power = 3;
		break;
	case ITEM_bomb:
		ItemName = L"��ź";
		itemImage = "bomb_3";
		origin = "bomb_3";
		effect = "3x3_explosion";
		this->power = 100;
		break;
	case ITEM_dirt_block:
		ItemName = L"��";
		itemImage = "dirt_block";
		origin = "dirt_block";
		effect = "dirt_block";
		this->power = 0;
		this->isStackable = true;
		break;
	}

	p = IMAGE->FindImage(itemImage);
}
