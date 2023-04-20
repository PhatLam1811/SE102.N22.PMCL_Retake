#include "CMario.h"

#include "CAnimationManager.h"
#include "Utils.h"

CMario::CMario(float x, float y)
{
	this->x = x;
	this->y = y;

	this->vx = MARIO_WALKING_SPEED;
	this->vy = MARIO_WALKING_SPEED;

	this->dirX = 1;

	this->accelX = 0;
	this->accelY = 0;

	this->accelScale = MARIO_WALKING_ACCEL_SCALE;
	this->isSlowingDown = false;
}

// ====================================================

void CMario::SetHorizontalDir(int dirX)
{
	this->dirX = dirX;
}

void CMario::Run()
{
	if (this->accelScale != MARIO_RUNNING_ACCEL_SCALE)
	{
		this->accelScale = MARIO_RUNNING_ACCEL_SCALE;
	}
	else
	{
		this->accelScale = MARIO_WALKING_ACCEL_SCALE;
	}
}

void CMario::SpeedUp()
{
	// accelX increase overtime
	this->accelX += this->dirX * SPEED_INCREMENT;

	// accelX is limited by accelScale
	if (this->accelX > this->accelScale) this->accelX = this->accelScale;
	if (this->accelX < -this->accelScale) this->accelX = -this->accelScale;
}

void CMario::SlowDown() { this->isSlowingDown = true; }

void CMario::OnSlowDown()
{
	// accelX decrease overtime
	this->accelX += this->dirX * SPEED_DECREMENT;

	// stop if accelX & moving direction are opposite 
	if (this->accelX * this->dirX <= 0)
	{
		this->isSlowingDown = false;
		this->accelX = 0;
	}
}

void CMario::Move(DWORD elapsedTime)
{
	this->x += this->accelX * this->vx * elapsedTime;
}

// ====================================================

void CMario::Update(DWORD elapsedTime)
{
	if (this->isSlowingDown) this->OnSlowDown();

	this->Move(elapsedTime);

	return;
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}