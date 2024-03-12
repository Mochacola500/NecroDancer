#pragma once
#ifndef MYWINDOW_H
#define MYWINDOW_H
class MyWindow : public SingletonBase<MyWindow>
{
private:
	WNDCLASS mWndClass;

	HWND mHwnd;
	HINSTANCE mhInstance;
	RECT mClientRect;

	void CreateWindowClass();
	void RegisterCWindow();
	void CreateCWinodw();
	void ShowCWindow();
	void SetWindowSize();

public:
	const HWND& GetHwnd() const { return mHwnd; }
	const HINSTANCE& GethInstance() const { return mhInstance; }
	const RECT& GetWindowRect() const { return mClientRect; }

	////////////////////////////// 싱글톤 프렌드 및 생성자, 소멸자, 복사 및 대입 방지
private:
	friend class SingletonBase<MyWindow>;
	MyWindow();
	~MyWindow() = default;

public:
	MyWindow(const MyWindow&) = delete;
	const MyWindow& operator= (const MyWindow&) = delete;

};
#endif // !MYWINDOW_H
