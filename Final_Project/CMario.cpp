#include "CMario.h"

#include "CAnimationManager.h"
#include "Utils.h"

// ====================================================

CMario::CMario(float x, float y) : CBaseGameObject(x, y)
{
	this->vx = MARIO_WALKING_SPEED;
	this->vy = MARIO_WALKING_SPEED;

	this->dirX = 1;

	// p-meter fill up from 0-1
	this->powerMeter = 0.0f; 

	this->form = nullptr;

	this->isPowerUp = false;
	this->isSlowingDown = false;
	this->isSpeedingUp = false;
}

void CMario::PowerUp() { this->isPowerUp = this->isSpeedingUp; }

void CMario::OnSlowDown()
{
	if (this->ax == 0.0f || this->isSpeedingUp) return;

	// accelX decrease overtime
	this->ax += this->dirX * -SPEED_INCREMENT;

	// stop if accelX & moving direction are opposite 
	if (this->ax * this->dirX <= 0.0f) this->ax = 0.0f;

	// DebugOut(L"[INFO] ON SLOWING DOWN!\n");
}

void CMario::OnPowerUp()
{
	this->powerMeter += P_METER_INCREMENT;

	if (this->powerMeter >= MARIO_MAX_P_METER)
	{
		this->powerMeter = MARIO_MAX_P_METER;
		this->isMaxPower = true;
	}
}

void CMario::OnStopSpeedUp() { this->isSpeedingUp = false; }

void CMario::OnSpeedUp(int dirX)
{
	this->dirX = dirX;
	this->isSpeedingUp = true;

	// accelX increase overtime
	float scaleOvertime = this->dirX * SPEED_INCREMENT;

	this->ax += scaleOvertime;

	// accelX scale is limited
	float maxScale = this->powerMeter + MARIO_ACCEL_SCALE;

	if (this->ax > maxScale) this->ax = maxScale;
	if (this->ax < -maxScale) this->ax = -maxScale;

	//DebugOut(L"[INFO] ON SPEEDING UP!\n");
}

void CMario::Move(DWORD elapsedTime)
{
	this->x += this->ax * this->vx * elapsedTime;
	this->y += this->ay * this->vy * elapsedTime;
}

// ====================================================

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x - MARIO_BIG_BBOX_WIDTH / 2;
	top = this->y - MARIO_BIG_BBOX_HEIGHT / 2;
	right = left + MARIO_BIG_BBOX_WIDTH;
	bottom = top + MARIO_BIG_BBOX_HEIGHT;
}

void CMario::Update(DWORD elapsedTime, std::vector<CBaseGameObject*>* gameObjects)
{
	if (this->isPowerUp) this->OnPowerUp();
	this->OnSlowDown();	

	CCollisionManager::GetInstance()->Process(this, elapsedTime, gameObjects);
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}

// ====================================================

void CMario::OnNoCollision(DWORD elapsedTime)
{
	this->Move(elapsedTime);
}

void CMario::OnCollisionWith(CCollisionEvent* collisionEvent)
{

}
