#pragma once
#include "SingletonBase.h"
#define KEYMAX 256
class Input final : public SingletonBase<Input>
{
private:
	enum : int { KeyMax = 256 };
private:
	//중복 키 허용을 위해 이전 키와 현재 키 변수 사용
	std::bitset<KeyMax> mKeyPast;
	std::bitset<KeyMax> mKeyCurrent;
public:
	Input();
	virtual ~Input();

	void Update();
	//한번 눌렸다면
	bool IsOnceKeyUp(int key);
	//키에서 손을 땠다면
	bool IsOnceKeyDown(int key);
	//키를 누르고 있다면
	bool IsStayKeyDown(int key);
	//토글 키
	bool ToggleKey(int key);

	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


