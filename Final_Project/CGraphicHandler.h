#pragma once

#include <d3d10.h>
#include <d3dx10.h>

#include "CTexture.h"

class CGraphicHandler
{
private:
	static CGraphicHandler* instance;
	
	// window
	HWND hWnd;									// Window handle
	HINSTANCE hInstance;
	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	// directX
	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????
	ID3D10SamplerState* pPointSamplerState;

public:
	// game handler accessors
	static CGraphicHandler* GetInstance();

	// directX handlers accessors
	ID3D10Device* GetDirect3DDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D10RenderTargetView* GetRenderTargetView();
	ID3DX10Sprite* GetSpriteHandler();
	ID3D10BlendState* GetAlphaBlending();
	void SetPointSamplerState();

	// window size accessors
	int GetBackBufferWidth();
	int GetBackBufferHeight();

	void Init(HWND hWnd, HINSTANCE hInstance);

	void Render(float x, float y, CTexture* tex, RECT* rect, float alpha, int sprite_width, int sprite_height);

	~CGraphicHandler();
};

