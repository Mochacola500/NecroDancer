#pragma once

#ifndef LIBRARY_H
#define LIBRARY_H
/////////////////////////////////////////////////////

//���̷�Ʈ2D ���̺귯��
#pragma comment(lib, "d2d1.lib")
#include <D2D1.h>
#include <d2d1helper.h>

//���̷�Ʈ Write ���̺귯��
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>

//WIC ���̺귯��
#pragma comment(lib, "WindowsCodecs.lib")
#include <wincodec.h>
using namespace D2D1;

//Fmod ���̺귯�� - ����
#include "SOUND/inc/fmod.hpp"
#ifndef _WIN32
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
#else
#pragma comment (lib, "SOUND/lib/fmodex64_vc.lib")
#endif // !_WIN32

using namespace FMOD;
/////////////////////////////////////////////////////
#endif // !LIBRARY_H