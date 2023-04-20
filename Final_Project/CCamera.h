#pragma once

#include "CBaseGameObject.h"

class CCamera : public CBaseGameObject
{
public:
	CCamera(float x, float y);

	// Inherited via CBaseGameObject
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};

