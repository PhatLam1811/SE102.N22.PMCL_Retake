#include "CAssets.h"

// Singleton
CAssets* CAssets::instance = nullptr;

CAssets* CAssets::GetInstance()
{
	if (instance == NULL) instance = new CAssets();
	return instance;
}