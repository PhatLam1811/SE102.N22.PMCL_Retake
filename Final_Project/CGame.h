#pragma once

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "CAssets.h"
#include "CGameObjects.h"

#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100

using namespace std;

class CGame
{
private:
	static CGame* instance;

	static LPASSETS assets;
	static LPGAMEOBJECTS gameObjects;

	HWND hWnd;									// Window handle
	HINSTANCE hInstance;
	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????
	ID3D10SamplerState* pPointSamplerState;

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);
	
	static CGame* GetInstance();

	LPASSETS GetAssetHandler();
	LPGAMEOBJECTS GetGameObjsHandler();

	int GetBackBufferWidth();
	int GetBackBufferHeight();

	ID3D10Device* GetDirect3DDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D10RenderTargetView* GetRenderTargetView();
	ID3DX10Sprite* GetSpriteHandler();
	ID3D10BlendState* GetAlphaBlending();

	void SetPointSamplerState();

	~CGame();
};

typedef CGame* LPGAME;
