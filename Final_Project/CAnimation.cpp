#include "CAnimation.h"
#include "CAssetManager.h"
#include "Utils.h"

CAnimation::CAnimation(int defaultDuration)
{
	this->defaultDuration = defaultDuration;
	this->lastFrameTime = -1;
	this->currentFrame = -1;
}

void CAnimation::Add(int spriteId, DWORD duration)
{
	int frameDuration = duration;
	if (duration == 0) frameDuration = this->defaultDuration;

	CSprite* sprite = CAssetManager::GetInstance()->GetSprite(spriteId);

	if (sprite == nullptr)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	CAnimationFrame* frame = new CAnimationFrame(sprite, frameDuration);
	this->animationFrames.push_back(frame);
}

void CAnimation::Play(float x, float y)
{
	ULONGLONG now = GetTickCount64();

	if (this->currentFrame == -1)
	{
		this->currentFrame = 0;
		this->lastFrameTime = now;
	}
	else
	{
		DWORD duration = this->animationFrames[this->currentFrame]->GetDuration();
		if (now - this->lastFrameTime > duration)
		{
			this->currentFrame++;
			this->lastFrameTime = now;
			if (this->currentFrame == this->animationFrames.size()) this->currentFrame = 0;
		}

	}

	this->animationFrames[this->currentFrame]->GetSprite()->Render(x, y);
}
