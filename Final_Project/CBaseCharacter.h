#pragma once

#include "CBaseGameObject.h"

class CBaseCharacter : public CBaseGameObject
{
protected:
	float vx;
	float vy;

	float accelX;
	float accelY;

	float dirX;

public:
};
