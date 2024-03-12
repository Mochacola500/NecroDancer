#pragma once

#ifndef COMMON_SINGLETON_H
#define COMMON_SINGLETON_H
namespace Common
{
	// ½Ì±ÛÅæ ¸ÅÅ©·Î »ó¼ö
	////////////////////////////////////

#define WINDOW MyWindow::Get()
#define D2DRENDER D2DRenderer::Get()
#define IMAGE ImageManager::Get()
#define SOUND SoundManager::Get()
#define SCENE SceneManager::Get()
#define KEY Input::Get()
#define TIME Timer::Get()
#define CAMERA Camera::Get()

	////////////////////////////////////
};
#endif // !COMMON_SINGLETON_H
