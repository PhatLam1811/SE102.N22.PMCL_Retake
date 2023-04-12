#include <fstream>

#include "CSpriteManager.h"
#include "CConfigManager.h"
#include "GameDefine.h"
#include "Utils.h"

// Singleton
CSpriteManager* CSpriteManager::instance = nullptr;

CSpriteManager* CSpriteManager::GetInstance()
{
	if (instance == nullptr) instance = new CSpriteManager();
	return instance;
}

CSpriteManager::CSpriteManager() { return; }
CSpriteManager::CSpriteManager(const CSpriteManager*) { return; }
CSpriteManager::~CSpriteManager() { delete this; }

void CSpriteManager::LoadAssets(wstring assetsFilePath)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetsFilePath);

	ifstream f;
	f.open(assetsFilePath);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: CConfigManager::GetInstance()->ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: CConfigManager::GetInstance()->ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetsFilePath);
}

CSprite* CSpriteManager::GetSprite(int spriteId) { return this->sprites[spriteId]; }

void CSpriteManager::Clear()
{
	for (auto x : this->sprites)
	{
		CSprite* s = x.second;
		delete s;
	}

	this->sprites.clear();
}
