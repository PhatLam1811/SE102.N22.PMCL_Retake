#pragma once

#include "CGraphicHandler.h"

#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100

using namespace std;

class CGameManager
{
private:
	static CGameManager* instance;

	// handlers
	CGraphicHandler* graphicHandler;

public:
	static CGameManager* GetInstance();
	
	// handler accessors
	CGraphicHandler* GetGraphicHandler();

	// init handlers
	void Init(HWND hWnd, HINSTANCE hInstance);
};
