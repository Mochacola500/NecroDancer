#include "stdafx.h"
#include "Fade.h"

namespace NecroMinecraft
{
	Fade::Fade() 
		: m_Dark(0, 0, WINSIZE_X, WINSIZE_Y)
	{

	}

	Fade::~Fade()
	{
	}

	void Fade::Initialize(FADE_TYPE type)
	{
		this->m_type = type;
		m_type == FADE_TYPE::FADE_IN ? m_alpha = 0.f : m_alpha = 1.5f;
	}

	bool Fade::Update()
	{
		if (m_type == FADE_TYPE::FADE_IN)
		{
			m_alpha += 0.01f * DELTA_TIME ;
			if (m_alpha > 1.f) {
				return true;
			}
		}
		else
		{
			m_alpha -= 0.01f * DELTA_TIME;
			if (m_alpha < 0.f) {
				return true;
			}
		}
		return false;
	}

	void Fade::Render()
	{
		D2DRENDER->FillRectangle(m_Dark, ColorF::Black, m_alpha);
	}
}
