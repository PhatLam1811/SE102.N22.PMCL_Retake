#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <typeinfo>

#include "CGraphicManager.h"
#include "GameDefine.h"


#define DIR_LEFT -1
#define DIR_RIGHT 1

class CBaseGameObject
{
protected:
	// position
	float x;
	float y;

	// velocities
	float vx;
	float vy;

	// accelerators
	float ax;
	float ay;

	// horizontal facing direction
	int dirX;

public:
	CBaseGameObject(float x, float y)
	{
		this->x = x;
		this->y = y;

		this->vx = 0.0f;
		this->vy = 0.0f;

		this->ax = 0.0f;
		this->ay = 0.0f;

		this->dirX = DIR_RIGHT;
	}

	std::string GetType()
	{
		return typeid(*this).name();
	}

	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void GetPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y;
	}

	void SetSpeed(float vx, float vy)
	{
		this->vx = vx;
		this->vy = vy;
	}
	void GetSpeed(float& vx, float& vy) 
	{
		vx = this->vx;
		vy = this->vy;
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void RenderBoundingBox()
	{
		float left, top, bottom, right;

		this->GetBoundingBox(left, top, right, bottom);

		CGraphicManager::GetInstance()->Render(
			this->x, this->y,
			ID_TEX_BBOX,
			left, top, right, bottom,
			BBOX_ALPHA, 0, 0);
	}

	virtual void Update(DWORD elapsedTime, std::vector<CBaseGameObject*>* collidableObjects = nullptr) = 0;
	virtual void Render() = 0;

	~CBaseGameObject() 
	{
		delete this;
	}
};
