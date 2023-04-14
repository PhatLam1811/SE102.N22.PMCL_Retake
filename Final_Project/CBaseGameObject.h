#pragma once

#include <Windows.h>

class CBaseGameObject
{
protected:
	float x;
	float y;

public:
	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void SetPositionX(float x);
	void SetPositionY(float y);
	float GetPositionX();
	float GetPositionY();

	virtual void Update(DWORD elapsedTime);
	virtual void Render();

	~CBaseGameObject();
};
