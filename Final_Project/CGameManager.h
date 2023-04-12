#pragma once

#include "CGraphicManager.h"
#include "CSceneManager.h"
#include "CConfigManager.h"
#include "CAnimationManager.h"

#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100

using namespace std;

class CGameManager
{
private:
	static CGameManager* instance;

	CGameManager();
	CGameManager(const CGameManager*);

public:
	static CGameManager* GetInstance();

	// accessors
	static CGraphicManager* GetGraphicManager();
	static CSceneManager* GetSceneManager();
	static CConfigManager* GetConfigManager();
	static CAnimationManager* GetAnimationManager();

	void Init(HWND hWnd, HINSTANCE hInstance);
	void Load(LPCWSTR gameFile);

	~CGameManager();
};
