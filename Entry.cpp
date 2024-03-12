#include "stdafx.h"

/**********************************************************************
@ 게임 실행
***********************************************************************/
inline int StartGame()
{
	return Game().GameProcess();
}

/**********************************************************************
@ 진입점
***********************************************************************/
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,                    
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	return StartGame();
}