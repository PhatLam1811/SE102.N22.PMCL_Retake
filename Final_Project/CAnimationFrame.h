#pragma once

#include "CSprite.h"

class CAnimationFrame
{
private:
	CSprite* sprite;
	DWORD duration;

public:
	CAnimationFrame(CSprite* sprite, DWORD duration) { this->sprite = sprite; this->duration = duration; }

	DWORD GetDuration() { return this->duration; }
	CSprite* GetSprite() { return this->sprite; }
};