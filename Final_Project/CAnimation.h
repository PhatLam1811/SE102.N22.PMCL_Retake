#pragma once
#include <vector>

#include "CAnimationFrame.h"

using namespace std;

class CAnimation
{
private:
	ULONGLONG lastFrameTime;
	int defaultDuration;
	int currentFrame;
	vector<CAnimationFrame*> animationFrames;

public:
	CAnimation(int defaultDuration = 100);

	void Add(int spriteId, DWORD duration = 0);
	void Play(float x, float y);
};
