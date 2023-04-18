#include <fstream>

#include "CMario.h"

#include "CPlayScene.h"
#include "CConfigManager.h"
#include "GameDefine.h"
#include "Utils.h"

CPlayScene::CPlayScene(int sceneId, wstring filePath) : CScene(sceneId, filePath)
{
	// subscribe to input manager

	this->isMarioLoaded = false;
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", this->filePath);

	ifstream f;
	f.open(this->filePath);

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

	CInputManager::GetInstance()->AssignKeyInputCallback(this);

	DebugOut(L"[INFO] Done loading scene  %s\n", this->filePath);

	DebugOut(L"[INFO] Scene game objects size : %zu\n", this->gameObjects.size());
}

void CPlayScene::AddGameObject(int objectId, float x, float y)
{
	CBaseGameObject* gameObject = nullptr;

	switch (objectId)
	{
	case OBJECT_TYPE_MARIO:
		if (this->isMarioLoaded)
		{
			DebugOut(L"[ERROR] MARIO object was loaded before!\n");
			return;
		}

		gameObject = new CMario(x, y);
		
		this->isMarioLoaded = true;

		DebugOut(L"[INFO] Mario has been loaded!\n");
		
		break;

		//case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
		//case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
		//case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;

		//case OBJECT_TYPE_PLATFORM:
		//{

		//	float cell_width = (float)atof(tokens[3].c_str());
		//	float cell_height = (float)atof(tokens[4].c_str());
		//	int length = atoi(tokens[5].c_str());
		//	int sprite_begin = atoi(tokens[6].c_str());
		//	int sprite_middle = atoi(tokens[7].c_str());
		//	int sprite_end = atoi(tokens[8].c_str());

		//	obj = new CPlatform(
		//		x, y,
		//		cell_width, cell_height, length,
		//		sprite_begin, sprite_middle, sprite_end
		//	);

		//	break;
		//}

		//case OBJECT_TYPE_PORTAL:
		//{
		//	float r = (float)atof(tokens[3].c_str());
		//	float b = (float)atof(tokens[4].c_str());
		//	int scene_id = atoi(tokens[5].c_str());
		//	obj = new CPortal(x, y, r, b, scene_id);
		//}
		//break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", objectId); return;
	}

	// General object setup
	gameObject->SetPosition(x, y);

	this->gameObjects.push_back(gameObject);
}

void CPlayScene::Unload()
{
	CInputManager::GetInstance()->UnAssignKeyInputCallback(this);
	return;
}

void CPlayScene::Update(DWORD dt) { }

void CPlayScene::Render()
{
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		this->gameObjects[i]->Render();
	}
}

void CPlayScene::OnKeyDown(BYTE* keyStates)
{
	DebugOut(L"On key down : %i\n", keyStates);
}

void CPlayScene::OnKeyPress(int keyCode)
{
	DebugOut(L"On key press : %i\n", keyCode);
}

void CPlayScene::OnKeyUp(int keyCode)
{
	DebugOut(L"On key up : %i\n", keyCode);
}
