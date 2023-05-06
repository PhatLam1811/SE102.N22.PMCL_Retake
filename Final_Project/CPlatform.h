#pragma once

#include "CBaseGameObject.h"

class CPlatform : public CBaseGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end);

	// Inherited via CBaseGameObject
	virtual bool IsDeleted() override { return false; }
	virtual bool IsBlocking() override { return true; }
	virtual bool IsCollidable() override { return false; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void RenderBoundingBox() override;

	virtual void OnNoCollision(DWORD elapsedTime) override;
	virtual void OnCollisionWith(CCollisionEvent* collisionEvent) override;

	virtual void Render() override;
	virtual void Update(DWORD dt, std::vector<CBaseGameObject*>* gameObjects) override {};
};

