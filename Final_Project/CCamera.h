#pragma once

#include "CBaseGameObject.h"

class CCamera : public CBaseGameObject
{
public:
	CCamera(float x, float y) : CBaseGameObject(x, y) {}

	// Inherited via CBaseGameObject
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD elapsedTime, std::vector<CBaseGameObject*>* gameObjects) {}
	virtual void Render() {}
};

