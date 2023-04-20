#pragma once

#include "CBaseGameObject.h"

#define DIR_LEFT -1
#define DIR_RIGHT 1

class CBaseCharacter : public CBaseGameObject
{
protected:
	float vx;
	float vy;

	float accelX;
	float accelY;

	int dirX;

public:
	CBaseCharacter(float x, float y) : CBaseGameObject(x, y) {};
};
