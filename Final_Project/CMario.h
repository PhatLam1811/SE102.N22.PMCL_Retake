#pragma once

#include "CBaseCharacter.h"

#define MARIO_WALKING_SPEED 0.1f

#define MARIO_MAX_P_METER 1.0f

#define MARIO_ACCEL_SCALE 1.0f

#define P_METER_INCREMENT 0.015f // 0.0015f
#define SPEED_INCREMENT 0.05f // 0.003f
// #define SPEED_DECREMENT -0.003f

class CMarioForm
{
public: void virtual Render() = 0;
};

class CMario : public CBaseCharacter
{
private:
	float powerMeter; // P meter


	bool isPowerUp;
	bool isMaxPower;
	bool isPowerOnCooldown;
	
	bool isSlowingDown;
	bool isSpeedingUp;

	CMarioForm* form;

public:
	CMario(float x, float y);

	void PowerUp();
	void OnStopSpeedUp();

	void OnSpeedUp(int dirX);
	void OnSlowDown();

	void OnPowerUp();
	
	void Move(DWORD elapsedTime);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
