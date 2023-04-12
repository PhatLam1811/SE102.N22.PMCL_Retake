#include "CConfigManager.h"
#include "CSceneManager.h"
#include "CAnimationManager.h"
#include "CAnimation.h"
#include "Utils.h"
#include "CSpriteManager.h"

CConfigManager* CConfigManager::instance = nullptr;
CConfigManager::CConfigManager() {}
CConfigManager::CConfigManager(const CConfigManager* objptr) {}

CConfigManager* CConfigManager::GetInstance()
{
	if (instance == nullptr) return new CConfigManager();
	return instance;
}

void CConfigManager::ParseSection_SETTINGS(string line, int& initialSceneId)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
	{
		initialSceneId = atoi(tokens[1].c_str());
		CSceneManager::GetInstance()->SetCurrentSceneId(initialSceneId);
	}
	else
		DebugOut(L"[ERROR] Unknown game setting: %s\n", ToWSTR(tokens[0]).c_str());
}

void CConfigManager::ParseSection_SCENES(string line, int& sceneId, wstring& scenePath)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	
	sceneId = atoi(tokens[0].c_str());
	
	scenePath = ToLPCWSTR(tokens[1]);   // file: ASCII format (single-byte char) => Wide Char
}

void CConfigManager::ParseSection_TEXTURES(string line)
{
}

void CConfigManager::ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	/*LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}*/

	// CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CConfigManager::ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	CSpriteManager::GetInstance()->LoadAssets(path.c_str());
}

void CConfigManager::ParseSection_OBJECTS(string line)
{
}

void CConfigManager::ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	CAnimation* ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());

	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimationManager::GetInstance()->Add(ani_id, ani);
}