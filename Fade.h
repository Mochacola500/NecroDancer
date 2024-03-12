#pragma once

namespace NecroMinecraft
{
	////////////////////////////////////
	// ���̵� Ÿ��
	enum FADE_TYPE
	{
		FADE_IN,
		FADE_OUT
	};

	////////////////////////////////////
	// ���̵� Ŭ����
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

