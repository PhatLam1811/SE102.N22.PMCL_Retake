#include "CInputManager.h"

CInputManager* CInputManager::instance = nullptr;

CInputManager* CInputManager::GetInstance()
{
	if (instance == nullptr) instance = new CInputManager();
	return instance;
}

CInputManager::CInputManager() { return; }
CInputManager::CInputManager(const CInputManager*) { return; }

CInputManager::~CInputManager() { delete this; }
