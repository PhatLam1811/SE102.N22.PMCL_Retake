#pragma once

#include "CBaseGameObject.h"

class CPlatform : public CBaseGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end);

	void Render();
	void Update(DWORD dt) {}
	// void GetBoundingBox(float& l, float& t, float& r, float& b);
	// void RenderBoundingBox();
};

