#include "CAssets.h"

// Singleton
LPASSETS CAssets::instance = NULL;

LPASSETS CAssets::GetInstance()
{
	if (instance == NULL) instance = new CAssets();
	return instance;
}