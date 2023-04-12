#pragma once

#include "CTexture.h"

class CSprite
{
private:
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	CTexture* texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;

public:
	CSprite(int id, int left, int top, int right, int bottom, CTexture* texture);

	D3DX10_SPRITE* GetSprite();
	D3DXMATRIX GetMatScaling();
	void SetMatWorld(D3DXMATRIX matWorld);

	void Render(float positionX, float positionY);
};
