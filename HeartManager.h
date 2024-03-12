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
		comboText = L"현재 코인 배수 : ";
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

		// 바 이동처리 ㅎㅎ
		//////////////////////////////////////
		for (auto& update : m_Bars) {
			update.get()->Update(m_Speed);
		}

		//////////////////////////////////////
		// 이미지용 하드코딩;
		if (m_BitUp) {
			m_BitUp--;
		}
		else {
			m_Heart_bit = { 0,0 };
		}
		//////////////////////////////////////
		// 충돌 체크 못하고 박힘
		bool isonce = false; // 두개바 올때 하나 크릵 한점수 하드코딩 ㅏㄴ중에 패치
		activeMove = false;

		for (size_t i = 0; i < m_Bars.size(); ++i) {
			if (IntersectRect(this->m_Bar_Check, m_Bars[i].get()->m_Rect)) {

				if (m_Bars[i]->life) {
					m_Bars[i].get()->life = false;
					if (!isonce) { // 두개바ㅓ 하나일때 일점용 하드코딩

						isonce = true;
						m_BitUp = 8;
						m_Heart_bit = { 1,0 };
						// 정확히 못눌러도 바가 도착했으니 빵빵
						SOUND->Play("sfx_missedbeat");

						
						TextEvent* comboFail = new TextEvent(L"빗나감!", 25.f);
						comboFail->SetEvent(m_Heart_Center, TextOption::DISAPPEAR, -2.0f, 90, false);
						m_event.push_back(comboFail);
						
						if (coinMulti > 1)
						{
							TextEvent* comboFail = new TextEvent(L"코인 배수 사라짐", 25.f);
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

	// 캐릭터 키입력시 발동
	void CheckBit()
	{
		bool isonce = false; // 두개바 올때 하나 크릵 한점수 하드코딩 ㅏㄴ중에 패치
		for (size_t i = 0; i < m_Bars.size(); ++i) {
			if (IntersectRect(this->m_Check, m_Bars[i].get()->m_Rect)) {

				if (m_Bars[i]->life) {
					m_Bars[i].get()->life = false;
					
					m_BitUp = 8;
					m_Heart_bit = { 1,0 };
					if (!isonce) { // 두개바ㅓ 하나일때 일점용 하드코딩
					// 정확히 눌렀으니 하트 빵빵
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
	vector<unique_ptr<Bar>>m_Bars;     // 바
	float m_Speed;           // 이동속도
	Image* m_Heart_Image;    // 하트
	Vector2 m_Heart_Center;  // 하트 위치
	Vector2 m_Heart_bit;     // 하트 뛰는 타이밍

	FloatRect m_Check;
	FloatRect m_Bar_Check_fail; // 바확인 렉트 실패용
	FloatRect m_Bar_Check;   // 바 확인렉트

	FloatRect m_Spawn_Left;  // 좌측 바ㅏ 스폰
	FloatRect m_Spawn_Right; // 우측 바프솦
	int m_BitUp;             // 하트 이미지 변경주기
};