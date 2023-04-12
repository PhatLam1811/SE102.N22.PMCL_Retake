#include "CAnimationManager.h"
#include "Utils.h"

CAnimationManager* CAnimationManager::instance = nullptr;

CAnimationManager* CAnimationManager::GetInstance()
{
	if (instance == nullptr) instance = new CAnimationManager();
	return instance;
}

CAnimationManager::CAnimationManager() { return; }
CAnimationManager::CAnimationManager(const CAnimationManager*) { return; }
CAnimationManager::~CAnimationManager() { delete this; }

void CAnimationManager::Add(int animationId, CAnimation* animation)
{
	if (this->animations[animationId] != nullptr)
		DebugOut(L"[WARNING] Animation %d already exists\n", animationId);

	this->animations[animationId] = animation;
}

CAnimation* CAnimationManager::GetAnimation(int animationId)
{
	CAnimation* animation = this->animations[animationId];
	if (animation == nullptr)
		DebugOut(L"[ERROR] Animation ID %d not found\n", animationId);
	return animation;
}

void CAnimationManager::Clear()
{
	for (auto x : this->animations)
	{
		CAnimation* animation = x.second;
		delete animation;
	}

	this->animations.clear();
}
