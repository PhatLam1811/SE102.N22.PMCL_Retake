#pragma once

#include "CBaseCharacter.h"

#define MARIO_RUNNING_SPEED 0.2f
#define MARIO_WALKING_SPEED 0.1f

#define MARIO_WALKING_ACCEL_SCALE 1.0f
#define MARIO_RUNNING_ACCEL_SCALE 2.0f

#define SPEED_INCREMENT 0.05f
#define SPEED_DECREMENT -0.08f

class CMarioForm
{
public: void virtual Render() = 0;
};

class CMario : public CBaseCharacter
{
private:
	float accelScale;
	bool isSlowingDown;

	CMarioForm* form;

public:
	CMario(float x, float y);

	void SetHorizontalDir(int dirX);

	void Run();
	void SpeedUp();
	void SlowDown();
	void OnSlowDown();	
	void Move(DWORD elapsedTime);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
