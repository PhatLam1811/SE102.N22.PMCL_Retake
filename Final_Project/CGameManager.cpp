#include <fstream>

#include "CGameManager.h"
#include "GameDefine.h"
#include "Utils.h"

CGameManager* CGameManager::instance = nullptr;

CGameManager* CGameManager::GetInstance()
{
	if (instance == nullptr) instance = new CGameManager();
	return instance;
}

CGameManager::CGameManager() { return; }
CGameManager::CGameManager(const CGameManager*) { return; }
CGameManager::~CGameManager() { delete this; }

CConfigManager* CGameManager::GetConfigManager() { return CConfigManager::GetInstance(); }
CAssetManager* CGameManager::GetAssetManager() { return CAssetManager::GetInstance(); }
CGraphicManager* CGameManager::GetGraphicManager() { return CGraphicManager::GetInstance(); }
CAnimationManager* CGameManager::GetAnimationManager() { return CAnimationManager::GetInstance(); }
CSceneManager* CGameManager::GetSceneManager() { return CSceneManager::GetInstance(); }
CInputManager* CGameManager::GetInputManager() { return CInputManager::GetInstance(); }

void CGameManager::Init(HWND hWnd, HINSTANCE hInstance) { GetGraphicManager()->Init(hWnd, hInstance); }

void CGameManager::Load(LPCWSTR gameFile)
{
	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[TEXTURES]") { section = GAME_FILE_SECTION_TEXTURES; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line[0] == '[')
		{
			section = GAME_FILE_SECTION_UNKNOWN;
			DebugOut(L"[ERROR] Unknown section: %s\n", ToLPCWSTR(line));
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS:
		{
			int initialSceneId;

			GetConfigManager()->ParseSection_SETTINGS(line, initialSceneId);
			GetSceneManager()->SetCurrentScene(initialSceneId);

			break;
		}

		case GAME_FILE_SECTION_SCENES:
		{
			int sceneId; wstring scenePath;

			GetConfigManager()->ParseSection_SCENES(line, sceneId, scenePath);
			GetSceneManager()->AddScene(sceneId, scenePath);

			break;
		}

		case GAME_FILE_SECTION_TEXTURES:
		{
			GetConfigManager()->ParseSection_TEXTURES(line); 
			
			break;
		}
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);
}

void CGameManager::Start() { GetSceneManager()->GetCurrentScene()->Load(); }
