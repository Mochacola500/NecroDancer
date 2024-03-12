#pragma once

#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H
namespace Common
{
   /**********************************************************************
   @ 디버그와 안전
   ***********************************************************************/
   // HRESULT 안전 확인
#define ASSERT_HRESULT_CHECK(p) {HRESULT hr = (p); assert(SUCCEEDED(hr));}
	
#ifdef _DEBUG
		// 콘솔 텍스트 색 변경
#define DEBUG_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)

	// 콘솔 텍스트 색 상수
#define DEBUG_WHITE 7
#define DEBUG_LIGHT_WHITE 15
#define DEBUG_BLUE 1
#define DEBUG_GREEN 2
#define DEBUG_CYAN 3
#define DEBUG_RED 4
#define DEBUG_YELLOW 6

	/*****************************************
	@ 콘솔 텍스트 출력
	@ color : 지정할 색 입력
	@ text  : 출력할 내용 입력
	******************************************/
#define DEBUG_TEXT(color, text) if(_DEBUG){ \
DEBUG_COLOR(color); cout << text << endl;}

	/*****************************************
	@ 작동 여부 확인 콘솔 텍스트 출력
	@ text    : 출력할 내용 입력
	@ confirm : 확인할 객체 입력
	@ check   : true 또는 false 상태가 참,거짓인지 입력
	******************************************/
#define DEBUG_CONFIRM(text, confirm, check) if(_DEBUG){     \
DEBUG_COLOR(DEBUG_LIGHT_WHITE); cout << text;               \
DEBUG_COLOR(DEBUG_WHITE);       cout << " [ ";              \
if(confirm){                                                \
if(check){DEBUG_COLOR(DEBUG_CYAN); cout << "COMPLETE";}     \
else     {DEBUG_COLOR(DEBUG_RED); cout << "FAIL";};         \
}else {                                                     \
if(check){DEBUG_COLOR(DEBUG_RED); cout << "FAIL";}          \
else     {DEBUG_COLOR(DEBUG_CYAN); cout << "COMPLETE";}};   \
DEBUG_COLOR(DEBUG_WHITE);       cout << " ]" << endl; }

	/*****************************************
	@ 반환 타입 확인 콘솔 텍스트 출력
	@ text : 출력할 내용 입력
	@ type : 확인할 변수의 형 입력
	******************************************/
#define DEBUG_GET_TYPE(text, type) if(_DEBUG){              \
DEBUG_COLOR(DEBUG_LIGHT_WHITE); cout << text;               \
DEBUG_COLOR(DEBUG_WHITE);       cout << " \" ";             \
DEBUG_COLOR(DEBUG_GREEN);       cout << typeid(type).name();\
DEBUG_COLOR(DEBUG_WHITE);       cout << " \"" << endl; }

#else
#define DEBUG_COLOR(color)
#define DEBUG_TEXT(color, text)
#define DEBUG_CONFIRM(text, confirm)
#define DEBUG_GET_TYPE(text, type)

#endif // !_DEBUG || DEBUG
}
#endif // !COMMON_DEBUG_H