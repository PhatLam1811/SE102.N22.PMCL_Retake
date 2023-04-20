#include "CPlatform.h"
#include "CGameManager.h"

CPlatform::CPlatform(
	float x, float y, 
	float cell_width, float cell_height, int length, 
	int sprite_id_begin, int sprite_id_middle, int sprite_id_end)
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
