#include "CMario.h"
#include "CAnimationManager.h"

CMario::CMario(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD elapsedTime)
{
	return;
}

void CMario::Render()
{
	CAnimationManager::GetInstance()->GetAnimation(501)->Play(this->x, this->y);
}