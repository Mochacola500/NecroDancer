#include "stdafx.h"
#include "Input.h"


/****************************************************
## Input ##
*****************************************************/
Input::Input()
{
	//ó���� ��� Ű�� �������� ���� ���·� �ʱ�ȭ
	mKeyCurrent.reset();
	mKeyPast.reset();
}
Input::~Input() {}

/****************************************************
## Update ##
*****************************************************/
void Input::Update()
{
	//��� ����Ű�� ����Ű�� �������ش�
	mKeyPast = mKeyCurrent;
}

bool Input::IsOnceKeyDown(int key)
{
	//�ش� Ű�� ���� ����
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//�� Ű�� �������� �ʾҴٸ�
		if (!mKeyPast[key])
		{
			//����Ű�� ���� ���·� �ٲٰ� return true
			mKeyCurrent.set(key, true);
			return true;
		}
	}
	//�ش� Ű�� ������ ���� ����
	else mKeyCurrent.set(key, false);   //����Ű�� ������ ���� ���·� �ٲ�

	return false;
}

bool Input::IsOnceKeyUp(int key)
{
	//�ش� Ű�� ���� ����					����Ű�� ���� ���·� �ٲ�
	if (GetAsyncKeyState(key) & 0x8000) mKeyCurrent.set(key, true);
	//�ش� Ű�� ������ ���� ����
	else
	{
		//�� Ű�� �����־��ٸ�
		if (mKeyPast[key])
		{
			//����Ű�� ������ ���� ���·� �ٲٰ� return true
			mKeyCurrent.set(key, false);
			return true;
		}
	}

	return false;
}

bool Input::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool Input::ToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

LRESULT Input::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
		CAMERA->InputZoom((SHORT)HIWORD(wParam));
		break;
	default:
		break;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}