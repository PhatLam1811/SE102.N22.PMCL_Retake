#pragma once

#include "CConfigManager.h"
#include "CAssetManager.h"
#include "CGraphicManager.h"
#include "CAnimationManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"

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
	static CConfigManager* GetConfigManager();
	static CAssetManager* GetAssetManager();
	static CGraphicManager* GetGraphicManager();
	static CAnimationManager* GetAnimationManager();
	static CSceneManager* GetSceneManager();
	static CInputManager* GetInputManager();

	void Init(HWND hWnd, HINSTANCE hInstance);
	void Load(LPCWSTR gameFile);
	void Start();

	~CGameManager();
};
