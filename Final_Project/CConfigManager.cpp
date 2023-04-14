#include "CConfigManager.h"
#include "CSceneManager.h"
#include "CAssetManager.h"
#include "CAnimationManager.h"
#include "CAnimation.h"
#include "GameDefine.h"
#include "Utils.h"

CConfigManager* CConfigManager::instance = nullptr;

CConfigManager* CConfigManager::GetInstance()
{
	if (instance == nullptr) return new CConfigManager();
	return instance;
}

CConfigManager::CConfigManager() { }
CConfigManager::CConfigManager(const CConfigManager* objptr) { }
CConfigManager::~CConfigManager() { delete this; }

void CConfigManager::ParseSection_SETTINGS(string line, int& initialSceneId)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
	{
		initialSceneId = atoi(tokens[1].c_str());
		CSceneManager::GetInstance()->SetCurrentScene(initialSceneId);
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
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int textureId = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);

	CAssetManager::GetInstance()->AddTexture(textureId, path.c_str());
}

void CConfigManager::ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	CAssetManager::GetInstance()->LoadAssets(path.c_str());
}

void CConfigManager::ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

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

void CConfigManager::ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int spriteId = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int textureId = atoi(tokens[5].c_str());

	 CAssetManager::GetInstance()->AddSprite(spriteId, l, t, r, b, textureId);
}

void CConfigManager::ParseSection_OBJECTS(string line)
{
	DebugOut(L"ParseSection_OBJECTS entered!!!!");

	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CBaseGameObject* gameObject = nullptr;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		//if (player != NULL)
		//{
		//	DebugOut(L"[ERROR] MARIO object was created before!\n");
		//	return;
		//}
		//obj = new CMario(x, y);
		//player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
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
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	gameObject->SetPosition(x, y);


	//objects.push_back(obj);
}
