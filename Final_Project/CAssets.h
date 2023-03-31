#pragma once
#include <Windows.h>
#include <vector>

#include "CSprite.h"

using namespace std;

class CAssets
{
private:
	static CAssets* instance;

	vector<CSprite> sprites;

public:
	static CAssets* GetInstance();
};
