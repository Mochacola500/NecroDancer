#include "stdafx.h"

/**********************************************************************
@ ���� ����
***********************************************************************/
inline int StartGame()
{
	return Game().GameProcess();
}

/**********************************************************************
@ ������
***********************************************************************/
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,                    
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	return StartGame();
}