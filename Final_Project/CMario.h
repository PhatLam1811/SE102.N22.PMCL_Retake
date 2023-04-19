#pragma once

#include "CBaseCharacter.h"

#define DIR_LEFT -1
#define DIR_RIGHT 1

#define WALKING_SPEED 0.1f

#define SPEED_INCREMENT 0.05f
#define SPEED_DECREMENT -0.08f

class CMario : public CBaseCharacter
{
private:
	bool isSlowingDown;

public:
	CMario(float x, float y);

	void SetHorizontalDir(int dirX);

	void SpeedUp();
	void SlowDown();
	void OnSlowDown();
	
	void Move(DWORD elapsedTime);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
