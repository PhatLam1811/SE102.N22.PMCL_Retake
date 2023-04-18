#pragma once

#include "CBaseCharacter.h"

#define DIR_LEFT -1;
#define DIR_RIGHT 1;

class CMario : public CBaseCharacter
{
private:

	

public:
	CMario(float x, float y);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
