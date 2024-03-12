#pragma once

#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H
namespace Common
{
   /**********************************************************************
   @ ����׿� ����
   ***********************************************************************/
   // HRESULT ���� Ȯ��
#define ASSERT_HRESULT_CHECK(p) {HRESULT hr = (p); assert(SUCCEEDED(hr));}
	
#ifdef _DEBUG
		// �ܼ� �ؽ�Ʈ �� ����
#define DEBUG_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)

	// �ܼ� �ؽ�Ʈ �� ���
#define DEBUG_WHITE 7
#define DEBUG_LIGHT_WHITE 15
#define DEBUG_BLUE 1
#define DEBUG_GREEN 2
#define DEBUG_CYAN 3
#define DEBUG_RED 4
#define DEBUG_YELLOW 6

	/*****************************************
	@ �ܼ� �ؽ�Ʈ ���
	@ color : ������ �� �Է�
	@ text  : ����� ���� �Է�
	******************************************/
#define DEBUG_TEXT(color, text) if(_DEBUG){ \
DEBUG_COLOR(color); cout << text << endl;}

	/*****************************************
	@ �۵� ���� Ȯ�� �ܼ� �ؽ�Ʈ ���
	@ text    : ����� ���� �Է�
	@ confirm : Ȯ���� ��ü �Է�
	@ check   : true �Ǵ� false ���°� ��,�������� �Է�
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
	@ ��ȯ Ÿ�� Ȯ�� �ܼ� �ؽ�Ʈ ���
	@ text : ����� ���� �Է�
	@ type : Ȯ���� ������ �� �Է�
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