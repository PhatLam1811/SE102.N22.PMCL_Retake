#include "CSprite.h"
#include "CGameManager.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, CTexture* texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;

	float texWidth = (float)texture->getWidth();
	float texHeight = (float)texture->getHeight();

	// Set the sprite’s shader resource view
	this->sprite.pTexture = texture->getShaderResourceView();

	this->sprite.TexCoord.x = this->left / texWidth;
	this->sprite.TexCoord.y = this->top / texHeight;

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	this->sprite.TexSize.x = spriteWidth / texWidth;
	this->sprite.TexSize.y = spriteHeight / texHeight;

	this->sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

D3DX10_SPRITE* CSprite::GetSprite() { return &this->sprite; }
D3DXMATRIX CSprite::GetMatScaling() { return this->matScaling; }
void CSprite::SetMatWorld(D3DXMATRIX matWorld) { this->sprite.matWorld = matWorld; }

void CSprite::Render(float posX, float posY)
{
	CGameManager::GetInstance()->GetGraphicManager()->Render(this, posX, posY);
}
