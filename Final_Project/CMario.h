#pragma once

#include "CBaseCharacter.h"

class CMario : public CBaseCharacter
{
private:

public:
	CMario(float x, float y);

	// Inherited via CBaseCharacter
	virtual void Update(DWORD elapsedTime) override;
	virtual void Render() override;
};
