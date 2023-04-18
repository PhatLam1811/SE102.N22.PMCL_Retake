#include "CMario.h"
#include "CAnimationManager.h"

CMario::CMario(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CMario::Move(int direction)
{
	this->ax += this->speedIncrement * direction;
}

void CMario::Update(DWORD elapsedTime)
{
	this->vx += this->ax * this->speed * elapsedTime;
	return;
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}