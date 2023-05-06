#pragma once

#include "CBaseGameObject.h"

#define MARIO_WALKING_SPEED 0.1f

#define MARIO_MAX_P_METER 1.0f

#define MARIO_ACCEL_SCALE 1.0f

#define P_METER_INCREMENT 0.015f // 0.0015f
#define SPEED_INCREMENT 0.05f // 0.003f

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

class CMarioForm
{
public: void virtual Render() = 0;
};

class CMario : public CBaseGameObject
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
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD elapsedTime, std::vector<CBaseGameObject*>* gameObjects) override;
	virtual void Render() override;

	virtual void OnNoCollision(DWORD elapsedTime) override;
	virtual void OnCollisionWith(CCollisionEvent* collisionEvent) override;
};
