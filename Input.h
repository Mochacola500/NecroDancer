#pragma once
#include "SingletonBase.h"
#define KEYMAX 256
class Input final : public SingletonBase<Input>
{
private:
	enum : int { KeyMax = 256 };
private:
	//�ߺ� Ű ����� ���� ���� Ű�� ���� Ű ���� ���
	std::bitset<KeyMax> mKeyPast;
	std::bitset<KeyMax> mKeyCurrent;
public:
	Input();
	virtual ~Input();

	void Update();
	//�ѹ� ���ȴٸ�
	bool IsOnceKeyUp(int key);
	//Ű���� ���� ���ٸ�
	bool IsOnceKeyDown(int key);
	//Ű�� ������ �ִٸ�
	bool IsStayKeyDown(int key);
	//��� Ű
	bool ToggleKey(int key);

	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


