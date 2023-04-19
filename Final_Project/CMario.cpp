#include "CMario.h"

#include "CAnimationManager.h"
#include "Utils.h"

CMario::CMario(float x, float y)
{
	this->x = x;
	this->y = y;

	this->vx = SPEED;
	this->vy = SPEED;

	this->dirX = 1;

	this->accelX = 0;
	this->accelY = 0;
}

void CMario::SetHorizontalDir(int dirX)
{
	this->dirX = dirX;
}

void CMario::Move()
{
	// accelX increase overtime
	this->accelX += this->dirX * SPEED_INCREMENT;

	// accelX range from -1 to 1 
	if (this->accelX > 1) this->accelX = 1;
	if (this->accelX < -1) this->accelX = -1;

	DebugOut(L"[INFO] Mario dir x : %f\n", this->dirX);
	DebugOut(L"[INFO] Mario accel x : %f\n", this->accelX);
}

void CMario::Update(DWORD elapsedTime)
{
	this->x += this->accelX * this->vx * elapsedTime;
	return;
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}