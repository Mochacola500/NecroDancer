#pragma once

namespace NecroMinecraft
{
	////////////////////////////////////
	// 페이드 타입
	enum FADE_TYPE
	{
		FADE_IN,
		FADE_OUT
	};

	////////////////////////////////////
	// 페이드 클래스
	class Fade
	{
	public:
		Fade();
		~Fade();

		void Initialize(FADE_TYPE type);
		bool Update();
		void Render();

	private:
		FloatRect m_Dark;
		FADE_TYPE m_type;
		float m_alpha;
	};
}

