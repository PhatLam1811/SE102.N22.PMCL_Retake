#pragma once

#include "CBaseCharacter.h"

#define DIR_LEFT -1;
#define DIR_RIGHT 1;


class CMario : public CBaseCharacter
{
private:
	const float speed = 3.0f;
	const float speedIncrement = 0.1f;

public:
	CMario(float x, float y);

	void Move(int direction);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
