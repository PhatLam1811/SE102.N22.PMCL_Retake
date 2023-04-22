#pragma once

#include <Windows.h>
#include <string>

class CBaseGameObject
{
protected:
	float x;
	float y;

public:
	CBaseGameObject(float x, float y);

	std::string GetType();
	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void SetPositionX(float x);
	void SetPositionY(float y);
	float GetPositionX();
	float GetPositionY();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void RenderBoundingBox();

	virtual void Update(DWORD elapsedTime) = 0;
	virtual void Render() = 0;

	~CBaseGameObject();
};
