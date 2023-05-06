#pragma once

#include "CBaseGameObject.h"

class CCamera : public CBaseGameObject
{
public:
	CCamera(float x, float y) : CBaseGameObject(x, y) {};

	// Inherited via CBaseGameObject
	virtual bool IsDeleted() override { return false; }
	virtual bool IsBlocking() override { return false; }
	virtual bool IsCollidable() override { return false; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {};

	virtual void OnNoCollision(DWORD elapsedTime) override {};
	virtual void OnCollisionWith(CCollisionEvent* collisionEvent) override {};

	virtual void Update(DWORD elapsedTime, std::vector<CBaseGameObject*>* collidableObjects) override {};
	virtual void Render() override {};
};
