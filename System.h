#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H
/////////////////////////////////////////////////////

// Singleton
#include "SingletonBase.h"

// Window Generator
#include "MyWindow.h"

// Sound
#include "SoundManager.h"

// Timer
#include "Timer.h"

// Input
#include "Input.h"

// Render
#include "D2DRenderer.h"
#include "Image.h"
#include "ImageManager.h"

#include "Animation.h"

// Object
#include "Object.h"
#include "Camera.h"
#include "Data.h"

#include "Item.h"
#include "Tile.h"

// Camera
#include "Particle.h"
#include "UI.h"
#include "ObjectManager.h"
#include "Bomb.h"
#include "useFunction.h"

#include "Player.h"
#include "Slime.h"
#include "Mimic.h"
#include "ShopKeeper.h"
#include "Bat.h"
#include "Elemental.h"
#include "Tresure.h"
#include "Wall.h"
#include "Door.h"

// Scene
#include "Scene.h"
#include "SceneManager.h"

// BinaryLoad
#include "Loading.h"
#include "LoadingScene.h"

#include "MapEditor.h"

#include "HeartManager.h"
#include "BeatManager.h"


////////////////
//Scene list
#include "Test.h" // ¸ÊÅø
#include "Zone1.h"
////////////////

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

// Game Run
#include "Game.h"

/////////////////////////////////////////////////////
#endif // !SYSTEM_H
