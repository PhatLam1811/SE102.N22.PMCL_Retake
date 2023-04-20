#include "CMario.h"

#include "CAnimationManager.h"
#include "Utils.h"

CMario::CMario(float x, float y) : CBaseCharacter(x, y)
{
	this->vx = MARIO_WALKING_SPEED;
	this->vy = MARIO_WALKING_SPEED;

	this->dirX = 1;

	this->accelX = 0.0f;
	this->accelY = 0.0f;

	this->powerMeter = 0.0f; // p-meter fill up from 1f to 2f (can't multiply zero with other scales)

	this->form = nullptr;

	this->isPowerUp = false;
	this->isSlowingDown = false;
	this->isSpeedingUp = false;
}

// ====================================================

void CMario::PowerUp() { this->isPowerUp = this->isSpeedingUp; }

void CMario::OnSlowDown()
{
	if (this->accelX == 0.0f || this->isSpeedingUp) return;

	// accelX decrease overtime
	this->accelX += this->dirX * -SPEED_INCREMENT;

	// stop if accelX & moving direction are opposite 
	if (this->accelX * this->dirX <= 0.0f) this->accelX = 0.0f;

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

	this->accelX += scaleOvertime;

	// accelX scale is limited
	float maxScale = this->powerMeter + MARIO_ACCEL_SCALE;

	if (this->accelX > maxScale) this->accelX = maxScale;
	if (this->accelX < -maxScale) this->accelX = -maxScale;

	//DebugOut(L"[INFO] ON SPEEDING UP!\n");
}

void CMario::Move(DWORD elapsedTime)
{
	this->x += this->accelX * this->vx * elapsedTime;
}

// ====================================================

void CMario::Update(DWORD elapsedTime)
{
	if (this->isPowerUp) this->OnPowerUp();
	this->OnSlowDown();

	//DebugOut(L"[INFO] Mario P meter : %f\n", this->powerMeter);
	//DebugOut(L"[INFO] Mario accel x : %f\n", this->accelX);

	this->Move(elapsedTime);

	return;
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}