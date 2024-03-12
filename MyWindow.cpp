#include "stdafx.h"
#include "MyWindow.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
const LPCWSTR WINNAME = L"Circle Empires";
/**************************************
@ ������ ����ü ����
***************************************/
void MyWindow::CreateWindowClass()
{
	mWndClass.cbClsExtra = 0;
	mWndClass.cbWndExtra = 0;
	mWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	mWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	mWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	mWndClass.hInstance = mhInstance;
	mWndClass.lpfnWndProc = WndProc;
	mWndClass.lpszClassName = WINNAME;
	mWndClass.lpszMenuName = WINNAME;
	mWndClass.style = CS_HREDRAW | CS_VREDRAW;
}

/**************************************
@ ������ ����ü ���
***************************************/
void MyWindow::RegisterCWindow()
{
	RegisterClass(&mWndClass);
}

/**************************************
@ ������ ����
***************************************/
void MyWindow::CreateCWinodw()
{
	mHwnd = CreateWindow(
		WINNAME, WINNAME, WS_OVERLAPPEDWINDOW,
		static_cast<int>(_WINSTART_X),
		static_cast<int>(_WINSTART_Y),
		WINSIZE_X, 
		WINSIZE_Y,
		NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);
}

/**************************************
@ ������ ���
***************************************/
void MyWindow::ShowCWindow()
{
	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);
}

/**************************************
@ ������ ���� ���Ͻ�
***************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return KEY->InputProc(hWnd, message, wParam, lParam);
}

/**************************************
@ ������ ũ�� ����
***************************************/
void MyWindow::SetWindowSize()
{
	GetClientRect(mHwnd, &mClientRect);

	//���� ������ ũ�� ����
	AdjustWindowRect(&mClientRect, CS_HREDRAW | CS_VREDRAW, false);

	SetWindowPos(mHwnd, NULL, mClientRect.left, mClientRect.top,
		(mClientRect.right - mClientRect.left), (mClientRect.bottom - mClientRect.top),
		SWP_NOZORDER | SWP_NOMOVE);

}

MyWindow::MyWindow()
	: mHwnd(nullptr)
	, mhInstance((HINSTANCE)GetModuleHandle(NULL))
	, mClientRect({0,0,0,0})
{
	this->CreateWindowClass();
	this->RegisterCWindow();
	this->CreateCWinodw();
	this->ShowCWindow();
	this->SetWindowSize();
}
