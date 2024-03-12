#pragma once

#ifndef __EVENT_TIME__
#define __EVENT_TIME__
template< typename EVENT_FUNCTION >
class EventTime
{
public:
	EventTime() = default;

	// maxTime 의 기본 8은 애니메이션 프레임을 의미
	// 주의 !! : 무한루프를 이벤트 큐에서 사용하지 말것!!!!
	EventTime(EVENT_FUNCTION event, float maxTime = 8.f, float count = 1.f, bool isLoop = false)
		: m_Event(event)        // 실행될 이벤트
		, m_Timer(0.f)          // 루프될 시간
		, m_MaxTime(maxTime)    // 발동할 시간
		, m_Count(count)        // 실행 회수
		, m_OverCheck(true)     // 이벤트 생존 플래그
		, m_IsLoop(isLoop)      // 무한 루프 확인
	{} // 이벤트 타이머 생성자

	void Update()
	{
		m_Timer += 60.f * TIME->getElapedTime(); // 60 프레임 기준으로 프레임 단위 돌림

		if (m_Timer > m_MaxTime) {
			if (m_Count) {
				m_Timer = 0.f;                // 타이머 초기화
				m_Event();                    // 이벤트 실행
				m_Count--;                    // 실행 회수 감소

				if (m_IsLoop || ! m_Count) {
					m_OverCheck = false;      // 이벤트 다음 타임의 제거 
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
