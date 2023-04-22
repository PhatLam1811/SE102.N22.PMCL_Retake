#include <typeinfo>
#include <string>

#include "CBaseGameObject.h"

#include "CGraphicManager.h"

#include "GameDefine.h"

CBaseGameObject::CBaseGameObject(float x, float y) { this->x = x; this->y = y; }
CBaseGameObject::~CBaseGameObject() { delete this; }

void CBaseGameObject::SetPosition(float x, float y) { this->x = x; this->y = y; }
void CBaseGameObject::GetPosition(float& x, float& y) { x = this->x; y = this->y; }
void CBaseGameObject::SetPositionX(float x) { this->x = x; }
void CBaseGameObject::SetPositionY(float y) { this->y = y; }
float CBaseGameObject::GetPositionX() { return this->x; }
float CBaseGameObject::GetPositionY() { return this->y; }

void CBaseGameObject::RenderBoundingBox()
{
	float left, top, bottom, right;

	this->GetBoundingBox(left, top, right, bottom);

	CGraphicManager::GetInstance()->Render(
		this->x, this->y, ID_TEX_BBOX,
		left, top, right, bottom,
		BBOX_ALPHA, 0, 0);
}

std::string CBaseGameObject::GetType()
{
	std::string type = typeid(*this).name();
	return type;
}