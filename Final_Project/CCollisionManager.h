#pragma once

#include <Windows.h>
#include <vector>

using namespace std;

class CBaseGameObject;

struct CCollisionEvent
{
	CBaseGameObject* src_obj;		// source object : the object from which to calculate collision
	CBaseGameObject* obj;			// the target object

	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
		CBaseGameObject* obj = nullptr, CBaseGameObject* src_obj = nullptr)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->src_obj = src_obj;
		this->isDeleted = false;
	}

	int WasCollided() { return this->t >= 0.0f && this->t <= 1.0f; }

	static bool compare(const CCollisionEvent* &a, CCollisionEvent* &b)
	{
		return a->t < b->t;
	}
};

class CCollisionManager
{
private:
	static CCollisionManager* __instance;

public:
	static CCollisionManager* GetInstance();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	CCollisionEvent* SweptAABB(
		CBaseGameObject* objSrc,
		DWORD dt,
		CBaseGameObject* objDest);
	
	void Scan(
		CBaseGameObject* objSrc,
		DWORD dt,
		vector<CBaseGameObject*>* objDests,
		vector<CCollisionEvent*>& coEvents);

	void Filter(
		CBaseGameObject* objSrc,
		vector<CCollisionEvent*>& coEvents,
		CCollisionEvent*& colX,
		CCollisionEvent*& colY,
		int filterBlock,
		int filterX,
		int filterY);

	void Process(CBaseGameObject* objSrc, DWORD dt, vector<CBaseGameObject*>* coObjects);
};
