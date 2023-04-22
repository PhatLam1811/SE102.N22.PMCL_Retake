#pragma once

#include "CBaseGameObject.h"

class CCamera : public CBaseGameObject
{
public:
	CCamera(float x, float y);

	// Inherited via CBaseGameObject
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};

