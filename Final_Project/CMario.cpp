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

	this->isSlowingDown = false;
}

// ====================================================

void CMario::SetHorizontalDir(int dirX)
{
	this->dirX = dirX;
}

void CMario::SpeedUp()
{
	// accelX increase overtime
	this->accelX += this->dirX * SPEED_INCREMENT;

	// accelX range from -1 to 1 
	if (this->accelX > 1) this->accelX = 1;
	if (this->accelX < -1) this->accelX = -1;
}

void CMario::SlowDown() { this->isSlowingDown = true; }

void CMario::OnSlowDown()
{
	// stop if accelX & moving direction are opposite 
	if (this->accelX * this->dirX <= 0)
	{
		this->isSlowingDown = false;
		this->accelX = 0;
	}
	else
	{
		// accelX decrease overtime
		this->accelX += this->dirX * SPEED_DECREMENT;
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