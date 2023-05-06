#include "CPlatform.h"
#include "CGameManager.h"

CPlatform::CPlatform(
	float x, float y, 
	float cell_width, float cell_height, int length, 
	int sprite_id_begin, int sprite_id_middle, int sprite_id_end) : CBaseGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->length = length;
	this->cellWidth = cell_width;
	this->cellHeight = cell_height;
	this->spriteIdBegin = sprite_id_begin;
	this->spriteIdMiddle = sprite_id_middle;
	this->spriteIdEnd = sprite_id_end;
}

void CPlatform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	left = this->x - cellWidth_div_2;
	top = this->y - this->cellHeight / 2;
	right = left + this->cellWidth * this->length;
	bottom = top + this->cellHeight;
}

void CPlatform::Render()
{
	if (this->length <= 0) return;
	
	float concreteSpritePosX = this->x;

	// Draw the start part of the platform
	CGameManager::GetAssetManager()->GetSprite(this->spriteIdBegin)->Render(concreteSpritePosX, this->y);

	// Update x position for the next sprite
	concreteSpritePosX += this->cellWidth;

	for (int i = 1; i < this->length - 1; i++)
	{
		CGameManager::GetAssetManager()->GetSprite(this->spriteIdMiddle)->Render(concreteSpritePosX, this->y);

		concreteSpritePosX += this->cellWidth;
	}

	if (this->length > 1)
	{
		CGameManager::GetAssetManager()->GetSprite(this->spriteIdEnd)->Render(concreteSpritePosX, this->y);
	}
}

void CPlatform::RenderBoundingBox()
{
	float left, top, bottom, right;

	this->GetBoundingBox(left, top, right, bottom);

	float xx = this->x - this->cellWidth / 2 + ((int)right - (int)left) / 2; // why though????

	CGraphicManager::GetInstance()->Render(
		xx, this->y, ID_TEX_BBOX,
		left, top, right, bottom,
		BBOX_ALPHA, 0, 0);
}

void CPlatform::OnNoCollision(DWORD elapsedTime) { }

void CPlatform::OnCollisionWith(CCollisionEvent* collisionEvent) { }
