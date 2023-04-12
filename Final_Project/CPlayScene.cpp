#include <fstream>

#include "CPlayScene.h"
#include "CConfigManager.h"
#include "GameDefine.h"
#include "Utils.h"


CPlayScene::CPlayScene(int sceneId, wstring filePath) : CScene(sceneId, filePath)
{
	// subscribe to input manager
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: CConfigManager::GetInstance()->ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: CConfigManager::GetInstance()->ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", filePath);
}

void CPlayScene::Unload()
{
	return;
}

void CPlayScene::Update(DWORD dt)
{
}

void CPlayScene::Render()
{
}
