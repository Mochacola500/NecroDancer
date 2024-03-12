#pragma once

struct Bar
{
	Image* m_Image;
	FloatRect m_Rect;
	Vector2 m_Image_Posiotion;
	bool m_IsLeft;
	bool life;
	bool death;
	float alpha;

	Bar() {}

	Bar(const string& imageName, FloatRect rect, bool isLeft)
		: m_Rect(rect)
		, m_Image_Posiotion(m_Rect.left, m_Rect.top)
		, m_IsLeft(isLeft)
		, life(true)
		, death(false)
		, alpha(0.0f)
	{
		this->m_Image = IMAGE->FindImage(imageName);
	}

	void Update(float speed)
	{
		if (life == false) {
			alpha -= 0.06f;
			if (alpha < 0.f) {
				death = true;
			}
		}
		else
		{
			if (m_IsLeft) {
				m_Rect.left += speed;
				m_Rect.right += speed;
			}
			else {
				m_Rect.left -= speed;
				m_Rect.right -= speed;
			}

			this->m_Image_Posiotion = { m_Rect.left, m_Rect.top };
		}
	}

	void Render()
	{
		if (!IsInWindow(m_Rect)) {
			if (alpha < 1.f) alpha += 0.03f;
			this->m_Image->SetSize(Vector2(10, 50));
			this->m_Image->FrameRender(this->m_Image_Posiotion, Vector2({ 0,0 }), false, alpha);
		}

	}
};

#define BAR_LENGTH 20
class HeartManager
{
private:
	vector<TextEvent*> m_event;
	TextEvent* showComboCount;
	wstring comboText;
	int disappear;

public:

	HeartManager() = default;
	~HeartManager() = default;

	void Init()
	{
		this->dodo = false;
		activeMove = false;

		m_Heart_Image = IMAGE->FindImage("TEMP_beat_heart");
		m_Spawn_Left = { 0, WINSIZE_Y - 152, 12, WINSIZE_Y };
		m_Spawn_Right = { WINSIZE_X, WINSIZE_Y - 152, WINSIZE_X + 12, WINSIZE_Y };
		m_Heart_Center = { (WINSIZE_X / 2) - 34, WINSIZE_Y - 172 };
		m_Bar_Check = { WINSIZE_X / 2 - 25, WINSIZE_Y - 152, WINSIZE_X / 2 + 25, WINSIZE_Y };
		m_Check = { WINSIZE_X / 2 - 125, WINSIZE_Y - 152, WINSIZE_X / 2 + 125, WINSIZE_Y };
		m_Heart_bit = { 0,0 };
		m_BitUp = 0;
		m_Speed = 8.f;
		comboText = L"���� ���� ��� : ";
		showComboCount = new TextEvent(comboText + to_wstring(coinMulti), 20.f, ColorF::Red);
		showComboCount->SetEvent(Vector2(m_Heart_Center.x - 40, m_Heart_Center.y + 90), TextOption::Keep, 0.0f, 90, false);
		coinComboCount = 0;
		disappear = 0;
	}

	void CreateBit(int gap)
	{
		m_Bars.push_back(make_unique<Bar>("TEMP_beat_marker", FloatRect(WINSIZE_X / 2 - gap, WINSIZE_Y - 147, WINSIZE_X / 2 - gap, WINSIZE_Y), true));
		m_Bars.push_back(make_unique<Bar>("TEMP_beat_marker", FloatRect(WINSIZE_X / 2 + gap, WINSIZE_Y - 147, WINSIZE_X / 2 + gap, WINSIZE_Y), false));
	}

	void Update()
	{
		if (disappear)
		{
			disappear--;
		}
		if (dododo) {
			this->CheckBit();
			dododo = false;
		}

		// �� �̵�ó�� ����
		//////////////////////////////////////
		for (auto& update : m_Bars) {
			update.get()->Update(m_Speed);
		}

		//////////////////////////////////////
		// �̹����� �ϵ��ڵ�;
		if (m_BitUp) {
			m_BitUp--;
		}
		else {
			m_Heart_bit = { 0,0 };
		}
		//////////////////////////////////////
		// �浹 üũ ���ϰ� ����
		bool isonce = false; // �ΰ��� �ö� �ϳ� ũ�� ������ �ϵ��ڵ� �����߿� ��ġ
		activeMove = false;

		for (size_t i = 0; i < m_Bars.size(); ++i) {
			if (IntersectRect(this->m_Bar_Check, m_Bars[i].get()->m_Rect)) {

				if (m_Bars[i]->life) {
					m_Bars[i].get()->life = false;
					if (!isonce) { // �ΰ��٤� �ϳ��϶� ������ �ϵ��ڵ�

						isonce = true;
						m_BitUp = 8;
						m_Heart_bit = { 1,0 };
						// ��Ȯ�� �������� �ٰ� ���������� ����
						SOUND->Play("sfx_missedbeat");

						
						TextEvent* comboFail = new TextEvent(L"������!", 25.f);
						comboFail->SetEvent(m_Heart_Center, TextOption::DISAPPEAR, -2.0f, 90, false);
						m_event.push_back(comboFail);
						
						if (coinMulti > 1)
						{
							TextEvent* comboFail = new TextEvent(L"���� ��� �����", 25.f);
							OBJECT->TileNonComboUpdate();
							comboFail->SetEvent(CAMERA->CorrecteLocation(&Vector2(OBJECT->GetPlayerCenter().x - 70, OBJECT->GetPlayerCenter().y + 10)), TextOption::DISAPPEAR, -2.0f,90, false);
							m_event.push_back(comboFail);
						}

						coinMulti = 1;
						coinComboCount = 0;
						showComboCount->SetText(comboText + to_wstring(coinMulti), 20.f);
					}
				}
			}

			if (IntersectRect(m_Check, m_Bars[i].get()->m_Rect)) {
				if (m_Bars[i].get()->life) {
					activeMove = true;
				}
			}

			if (m_Bars[i].get()->death == true) {
				m_Bars[i].release();
				m_Bars.erase(m_Bars.begin() + i);
			}
		}

	}
	void Render()
	{
		for (auto& render : m_Bars) {
			render.get()->Render();
		}
		m_Heart_Image->SetSize(Vector2(80, 100));
		this->m_Heart_Image->FrameRender(m_Heart_Center, m_Heart_bit);
		
		for (int i = 0; i < m_event.size(); ++i) {
			if (m_event[i]->life != false) {
				m_event[i]->Render();
			}
			else
			{
				m_event.erase(m_event.begin() + i);
				i--;
			}
		}
		if (!disappear)
		{
			showComboCount->Render();
		}
	}

	void ChangeSpeed(float speed)
	{
		this->m_Speed = speed;
	}

	// ĳ���� Ű�Է½� �ߵ�
	void CheckBit()
	{
		bool isonce = false; // �ΰ��� �ö� �ϳ� ũ�� ������ �ϵ��ڵ� �����߿� ��ġ
		for (size_t i = 0; i < m_Bars.size(); ++i) {
			if (IntersectRect(this->m_Check, m_Bars[i].get()->m_Rect)) {

				if (m_Bars[i]->life) {
					m_Bars[i].get()->life = false;
					
					m_BitUp = 8;
					m_Heart_bit = { 1,0 };
					if (!isonce) { // �ΰ��٤� �ϳ��϶� ������ �ϵ��ڵ�
					// ��Ȯ�� �������� ��Ʈ ����
						isonce = true;
						coinComboCount++;

						if (coinComboCount == 10)
						{
							coinMulti++;
							coinComboCount = 0;
							disappear = 30;
							OBJECT->TileComboUpdate();
							showComboCount->SetText(comboText + to_wstring(coinMulti), 20.f);

							TextEvent* heart = new TextEvent(comboText + to_wstring(coinMulti), 25.f,ColorF::Red);
							heart->SetEvent(Vector2(m_Heart_Center.x - 45, m_Heart_Center.y + 90), TextOption::HeartBeat, 0.2f, 90, false);
							m_event.push_back(heart);
						}
					}
				}
			}
		}
	}

	void Release()
	{
		for (auto* deleted : m_event) {
			SAFE_DELETE(deleted);
		}
		for (auto& deleted : m_Bars) {
			deleted.release();
		}
		m_Bars.clear();
	}
	bool dodo;

private:
	vector<unique_ptr<Bar>>m_Bars;     // ��
	float m_Speed;           // �̵��ӵ�
	Image* m_Heart_Image;    // ��Ʈ
	Vector2 m_Heart_Center;  // ��Ʈ ��ġ
	Vector2 m_Heart_bit;     // ��Ʈ �ٴ� Ÿ�̹�

	FloatRect m_Check;
	FloatRect m_Bar_Check_fail; // ��Ȯ�� ��Ʈ ���п�
	FloatRect m_Bar_Check;   // �� Ȯ�η�Ʈ

	FloatRect m_Spawn_Left;  // ���� �٤� ����
	FloatRect m_Spawn_Right; // ���� ������
	int m_BitUp;             // ��Ʈ �̹��� �����ֱ�
};