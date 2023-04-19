#pragma once

#include "CBaseCharacter.h"

#define DIR_LEFT -1
#define DIR_RIGHT 1

#define WALKING_SPEED 0.1f
#define SPEED_INCREMENT 0.05f

class CMario : public CBaseCharacter
{
private:

public:
	CMario(float x, float y);

	void SetHorizontalDir(int dirX);

	void Move();

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
