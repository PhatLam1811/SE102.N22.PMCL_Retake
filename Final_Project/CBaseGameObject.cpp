#include "CBaseGameObject.h"

CBaseGameObject::CBaseGameObject() { this->x = 0; this->y = 0; }

void CBaseGameObject::SetPosition(float x, float y) { this->x = x; this->y = y; }
void CBaseGameObject::GetPosition(float& x, float& y) { x = this->x; y = this->y; }
void CBaseGameObject::SetPositionX(float x) { this->x = x; }
void CBaseGameObject::SetPositionY(float y) { this->y = y; }
float CBaseGameObject::GetPositionX() { return this->x; }
float CBaseGameObject::GetPositionY() { return this->y; }

CBaseGameObject::~CBaseGameObject() { delete this; }
