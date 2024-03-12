#pragma once

#ifndef __EVENT_TIME__
#define __EVENT_TIME__
template< typename EVENT_FUNCTION >
class EventTime
{
public:
	EventTime() = default;

	// maxTime �� �⺻ 8�� �ִϸ��̼� �������� �ǹ�
	// ���� !! : ���ѷ����� �̺�Ʈ ť���� ������� ����!!!!
	EventTime(EVENT_FUNCTION event, float maxTime = 8.f, float count = 1.f, bool isLoop = false)
		: m_Event(event)        // ����� �̺�Ʈ
		, m_Timer(0.f)          // ������ �ð�
		, m_MaxTime(maxTime)    // �ߵ��� �ð�
		, m_Count(count)        // ���� ȸ��
		, m_OverCheck(true)     // �̺�Ʈ ���� �÷���
		, m_IsLoop(isLoop)      // ���� ���� Ȯ��
	{} // �̺�Ʈ Ÿ�̸� ������

	void Update()
	{
		m_Timer += 60.f * TIME->getElapedTime(); // 60 ������ �������� ������ ���� ����

		if (m_Timer > m_MaxTime) {
			if (m_Count) {
				m_Timer = 0.f;                // Ÿ�̸� �ʱ�ȭ
				m_Event();                    // �̺�Ʈ ����
				m_Count--;                    // ���� ȸ�� ����

				if (m_IsLoop || ! m_Count) {
					m_OverCheck = false;      // �̺�Ʈ ���� Ÿ���� ���� 
				}
			}
		}
	}

private:
	EVENT_FUNCTION m_Event;
	int m_Count;

	float m_Timer;
	float m_MaxTime;
	bool m_IsLoop;
	bool m_OverCheck;
};
#endif // !__EVENT_TIME__
