#pragma once

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

class NumberPrint
{
private:
	Image* num;

public:
	float alpha;

	NumberPrint() = default;
	~NumberPrint() = default;

	void Init(float alpha = 1.0f)
	{
		this->alpha = alpha;
		num = IMAGE->FindImage("TEMP_digits");
	}

	void Render(Vector2 position, int amount, Vector2 size, bool cal = false)
	{
		Vector2 location(0, 0);

		int eax = amount;
		int ead = amount;
		int less = amount;
		position.x -= 20;
		if (num != nullptr)
		{
			while (true)
			{

				if (less < 10)
				{
					location.x = less;
					num->SetAlpha(alpha);
					num->SetSize(size);
					num->Render(position, location, cal);
					break;
				}

				less = eax % 10;

				ead = eax;

				do
				{
					ead /= 10;

				} while (ead > 10);

				location.x = static_cast<int>(ead);
				eax = eax / 10;
				num->SetAlpha(alpha);
				num->SetSize(size);
				num->Render(position, location, cal);
				position.x += size.x + 1.f;

			}
		}
	}

};


class Animation
{
public:

	void SetDrawLocation(int asdf)
	{
		this->m_ImageFlipTable.y = static_cast<float>(asdf);
	}

	Animation() = default; // 사용자가 직접 입력해서 사용

	string GetName()
	{
		return m_Image->GetKey();
	}

	void Initialize(string image, Vector2* drawLocation, float maxCount = 6.f
		, float flipSpeed = 50 * TIME->getElapedTime())
	{
		key = image;
		m_Image = IMAGE->FindImage(image);
		m_ImageFlipTable = { 0.f, 0.f };
		m_Count = 0.f;
		m_MaxCount = maxCount;
		m_DrawLocation = drawLocation;
		alpha = 1.0f;
		ImageSize = m_Image->GetFrameSize();
		this->flipSpeed = flipSpeed;
		ImageCalibrated = { 0,0 };
		angle = 0.f;
	} // 초기화

	void Render(Direction direction)
	{
		if (direction == LEFT)
		{
			m_Image = IMAGE->FindImage(key + "_reverse");
		}
		else
		{
			m_Image = IMAGE->FindImage(key);
		}

		m_Image->SetAngle(angle);
		m_Image->SetSize(TILEIMAGESIZE);
		m_Image->FrameRender((*m_DrawLocation), m_ImageFlipTable, true, alpha);


		m_Count += flipSpeed;

		if (m_Count > m_MaxCount)
		{
			m_ImageFlipTable.x++;
			m_Count = 0.f;

			if (m_ImageFlipTable.x == m_Image->GetMaxFrameX())
			{
				m_ImageFlipTable.x = 0.f;
			}
		}

	}

	void Render()
	{
		m_Image->SetAngle(angle);
		m_Image->SetSize(ImageSize);
		m_Image->FrameRender((*m_DrawLocation) + ImageCalibrated, m_ImageFlipTable, true, alpha);
		m_Count += 60 * TIME->getElapedTime();

		if (m_Count > m_MaxCount)
		{
			if (m_ImageFlipTable.x < m_Image->GetMaxFrameX())
			{
				m_ImageFlipTable.x++;
				m_Count = 0.f;
			}
		}
	}

	void FrameRender(Vector2 pos)
	{
		m_Image->SetAngle(angle);
		m_Image->SetSize(Vector2(TILESIZE_X, TILESIZE_Y));
		m_Image->FrameRender((*m_DrawLocation) + ImageCalibrated, pos, true, alpha);
	}

	bool CheckLastImage()
	{
		if (m_ImageFlipTable.x == m_Image->GetMaxFrameX())
		{
			return true;
		}

		return false;
	}

	void SetImageSize(Vector2 size)
	{
		ImageSize = size;
	}

	void CalibratedImageLocation(Vector2 cali)
	{
		ImageCalibrated = cali;
	}

	void SetAlpha(float alpha)
	{
		this->alpha = alpha;
	}

	void SetAngle(float angle)
	{
		this->angle = angle;
	}

	void SetImageFlipTable()
	{
		m_ImageFlipTable.x = 0;
	}

	Image* m_Image;
private:
	string key;
	Vector2 m_ImageFlipTable;
	Vector2* m_DrawLocation;
	Vector2 ImageCalibrated;
	Vector2 ImageSize;

	float m_Count;
	float m_MaxCount;
	float alpha;
	float flipSpeed;
	float angle;
};

const float MOVE_EVENT_FRAME = 12.f;
const int MOVE_EVENT_SPEED = TILESIZE_X / static_cast<int>(MOVE_EVENT_FRAME);

struct MoveEvent
{
	float m_Count;
	float m_CountJump;
	float m_CountSleep;
	Vector2* m_Target;
	Direction m_Direction;
	bool updown;
	Vector2 MoveTarget;
	bool jumpDo;

	MoveEvent() {
		jumpDo = true;
	}
	void Initialize(Vector2* target, float maxCount = MOVE_EVENT_FRAME)
	{
		this->m_Target = target;
		this->m_Direction = RIGHT;
		this->m_Count = m_CountJump = MOVE_EVENT_FRAME;
		this->m_CountSleep = 0;
		updown = true;
	}

	bool MoveCompleteCheck()
	{
		return m_Count >= MOVE_EVENT_FRAME;
	}

	void MoveOrder(Direction direction, Vector2 position_ = { 0, 0 })
	{
		if (m_Count >= MOVE_EVENT_FRAME)
		{
			this->m_Direction = direction;
			this->m_Count = 0.f;
			MoveTarget = position_;
		}
	}

	void MoveOrder(Vector2 start, Vector2 end)
	{
		if (m_Count >= MOVE_EVENT_FRAME)
		{
			this->m_Direction = CalculateDirection(start, end);
			this->m_Count = 0.f;
		}
	}

	void Update()
	{
		if (m_Count < MOVE_EVENT_FRAME)
		{
			if (jumpDo) {
				Jump();
			}

			m_Count++;
			switch (m_Direction)
			{
			case LEFT: (*m_Target).x -= MOVE_EVENT_SPEED;
				break;
			case RIGHT: (*m_Target).x += MOVE_EVENT_SPEED;
				break;
			case UP: (*m_Target).y -= MOVE_EVENT_SPEED;
				break;
			case DOWN: (*m_Target).y += MOVE_EVENT_SPEED;
				break;
			}
		}
	}

	void UpdateN()
	{
		if (m_Count < MOVE_EVENT_FRAME)
		{
			m_Count++;
			switch (m_Direction)
			{
			case LEFT: (*m_Target).x -= MOVE_EVENT_SPEED;
				break;
			case RIGHT: (*m_Target).x += MOVE_EVENT_SPEED;
				break;
			case UP: (*m_Target).y -= MOVE_EVENT_SPEED;
				break;
			case DOWN: (*m_Target).y += MOVE_EVENT_SPEED;
				break;
			}
		}
	}

	void UpdateMoveTarget()
	{
		if (m_Count < MOVE_EVENT_FRAME)
		{
			m_Count++;
			(*m_Target).x += MOVE_EVENT_SPEED * MoveTarget.x;
			(*m_Target).y += MOVE_EVENT_SPEED * MoveTarget.y;
		}
	}

	void Jump()
	{
		if (m_Count < MOVE_EVENT_FRAME / 2) {
			(*m_Target).y -= 9.f;
		}
		else {
			(*m_Target).y += 9.f;
		}
		if (m_Count == 12) {
			(*m_Target).y += 9.f;
		}
	}

	void Jump(float power)
	{
		if (m_CountSleep < 0) {
			if (m_CountJump < MOVE_EVENT_FRAME)
			{
				if (m_CountJump < MOVE_EVENT_FRAME / 2) {
					(*m_Target).y -= power;
				}
				else {
					(*m_Target).y += power;
				}
				if (m_CountJump == 12) {
					(*m_Target).y -= power;
				}
				m_CountJump++;
			}
			else
			{
				m_CountSleep = 24.f;
				m_CountJump = 0.f;
			}
		}
		else
		{
			m_CountSleep--;
		}
	}
};

#endif // !__ANIMATION_H__
