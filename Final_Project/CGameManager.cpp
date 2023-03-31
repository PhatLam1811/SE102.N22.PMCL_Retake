#include "CGameManager.h"

CGameManager* CGameManager::instance = nullptr;

CGameManager* CGameManager::GetInstance()
{
	if (instance == NULL) instance = new CGameManager();
	return instance;
}

CGraphicHandler* CGameManager::GetGraphicHandler() { return CGraphicHandler::GetInstance(); }

void CGameManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	this->graphicHandler = CGraphicHandler::GetInstance();
	
	this->graphicHandler->Init(hWnd, hInstance);
}
