#pragma once

#include <unordered_map>

#include "CAnimation.h"

using namespace std;

class CAnimationManager
{
private:
	static CAnimationManager* instance;

	unordered_map<int, CAnimation*> animations;

	CAnimationManager();
	CAnimationManager(const CAnimationManager*);

public:
	static CAnimationManager* GetInstance();

	void Add(int animationId, CAnimation* animation);
	CAnimation* GetAnimation(int animationId);
	void Clear();

	~CAnimationManager();
};
