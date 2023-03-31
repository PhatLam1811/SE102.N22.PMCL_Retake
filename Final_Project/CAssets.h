#pragma once
#include <Windows.h>

using namespace std;

class CAssets
{
private:
	static CAssets* instance;

public:
	static CAssets* GetInstance();
};

typedef CAssets* LPASSETS;
