#pragma once

struct Transform
{
	Image* _image;      // 그릴 이미지
	Vector2 _size;      // 크기
	Vector2 _location;  // 위치
	Vector2 _savePosition;
	FloatRect _form;    // 크기 + 위치
	vector<Transform*> _childs; // 자식객체들
	IDWriteTextLayout* text;
	int gapx;
	int gapy;
	ColorF::Enum color;
	int textSize;

	void AddChild(Transform* p)
	{
		_childs.push_back(p);
	}

	~Transform()
	{
	}

	Transform(const Vector2& location, const Vector2& size)
	{
		this->Create(location, size);
	}

	Transform() = default;
	
	void Create(const Vector2& location, const Vector2& size,  string imageName = "")
	{
		this->_size = size;
		this->_location = location;
		this->_form = { location.x,
			location.y,
			location.x + size.x,
			location.y + size.y };
		_image = imageName == "" ? nullptr : IMAGE->FindImage(imageName);
		text = nullptr;
	}

	void TextUp(const wstring& text, int gax = 0, int gapy = 0, ColorF::Enum color = ColorF::White, int textSize = 20.f)
	{
		if (this->text != nullptr) this->text->Release();
		D2DRENDER->LayOutMake(&this->text, text, textSize);
		gapx = gax;
		this->gapy = gapy;
		this->color = color;
	}

	void SetSavePosition(const Vector2& p)
	{
		_savePosition = _location - p;
		if (_childs.size())
		{
			NotifyChildrenPosition(p);
		}
	}

	void Move(const Vector2& displacement)
	{
		this->_location = _savePosition  + displacement;
		this->_form = { 
			_location.x,
			_location.y,
			_location.x + _size.x,
			_location.y + _size.y };

		if (_childs.size())
		{
			NotifyChildren(displacement);
		}
	}

	void NotifyChildrenPosition(const Vector2& displacment)
	{
		for (auto& dispatch : _childs)
			dispatch->SetSavePosition(displacment);
	}

	void NotifyChildren(const Vector2& displacment)
	{
		for(auto& dispatch : _childs)
		dispatch->Move(displacment);
	}

	bool IsOnClick()
	{
		if (KEY->IsOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(_ptMouse, this->_form))
				return true;
		}
		return false;
	}


	bool IsOnClickStay()
	{
		if (KEY->IsStayKeyDown(VK_LBUTTON))
		{
			if (PtInRect(_ptMouse, this->_form))
				return true;
		}
		return false;
	}

	void Render()
	{
		if (_image != nullptr)
		{
			_image->SetSize(Vector2(_form.right - _form.left,
				_form.bottom - _form.top));
			_image->Render(Vector2(_form.left, _form.top));
		}
		else
		{
			D2DRENDER->FillRectangle(_form, ColorF::White);
		}
		if (text)
		D2DRENDER->RenderText(Vector2(
			_form.left + gapx,
			_form.top + gapy), 
			text,
			color);
	}
};

enum CreateType
{
	CreateType_Monster,
    CreateType_wall,
    CreateType_tile,
    CreateType_item,
    CreateType_misc,
	CreateType_Player,
	CreateType_size
};


class Switch
{
private:
	bitset<CreateType_size> bitCheck;
	CreateType target;

public:
	void OnCreate(int n)
	{
		if (n < bitCheck.size())
		{
			bitCheck.reset();
			bitCheck[n] = true;
			target = (CreateType)n;
		}
	}

	CreateType CreateTypeReturn()
	{
		return target;
	}
};

constexpr int MAPTOOL_PAGE_MAX = 30;

class MapEditor
{
public:
	void Init();
	void Release();
	void Update();
	void Save();
	void Load();
	void Render();

	void CreateSlotMake();

	MapEditor() = default;
	~MapEditor() = default;

	void NullCurrent();

private:
	ofstream m_FileSave;
	ifstream m_FileLoad;

	Transform Upper_bar;
	Transform form;
	Transform save_button;
	Transform load_button;

	Transform monster_button;
	Transform wall_button;
	Transform tile_button;
	Transform item_button;
	Transform player_button;
	Transform misc_button;
	Transform erase_button;
	Transform page_up;
	Transform page_down;

	Switch CreateTypeChecker;
	
	vector<Transform*> buttons;

	vector< Item* > itemInfo;
	vector< Object* > monsterInfo;
	vector< Wall* > wallInfo;
	vector< Tile* > tileInfo;
	vector< Image* > miscInfo;

	Vector2 ZeroVector2;

	Player* player;
	Object* currentMonster;
	Item*   currentItem;
	Wall*   currentWall;
	Tile*   currentTile;
	Image* currentMisc;

	Vector2 _pastMouse;

	int page;
	int monsterIndex;
	bool playerOne;
};


