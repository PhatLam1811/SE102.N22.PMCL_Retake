#include <fstream>
#include <typeinfo>

#include "CPlayScene.h"
#include "CGameManager.h"
#include "GameDefine.h"
#include "Utils.h"

CPlayScene::CPlayScene(int sceneId, wstring filePath) : CScene(sceneId, filePath) { this->player = nullptr; }

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
		case SCENE_SECTION_ASSETS: CGameManager::GetInstance()->GetConfigManager()->ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: CGameManager::GetInstance()->GetConfigManager()->ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", this->filePath);

	DebugOut(L"[INFO] Scene game objects size : %zu\n", this->gameObjects.size());

	CInputManager::GetInstance()->AssignKeyInputCallback(this);
}

void CPlayScene::AddGameObject(CBaseGameObject* gameObject)
{
	if (gameObject->GetType() == typeid(CMario).name())
	{
		if (this->player != nullptr)
		{
			DebugOut(L"[INFO] Mario has been loaded!\n"); return;
		}

		// assign game object as player if its class is CMario
		this->player = (CMario*)gameObject;

		DebugOut(L"[INFO] Mario has been loaded!\n");
	}

	this->gameObjects.push_back(gameObject);
}

void CPlayScene::Unload()
{
	CInputManager::GetInstance()->UnAssignKeyInputCallback(this);
	return;
}

void CPlayScene::Update(DWORD dt) 
{ 
	this->player->Update(dt);

	// Update camera to follow mario
	float camX = this->player->GetPositionX();
	float camY = this->player->GetPositionY();

	int backBufferWidth = CGameManager::GetInstance()->GetGraphicManager()->GetBackBufferWidth();
	int backBufferHeight = CGameManager::GetInstance()->GetGraphicManager()->GetBackBufferHeight();

	camX -= backBufferWidth / 2;
	camY -= backBufferHeight / 2;

	if (camX < 0) camX = 0;

	this->SetCamPos(camX, 0.0f /*cy*/);
}

void CPlayScene::Render()
{
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		this->gameObjects[i]->Render();
	}
}

void CPlayScene::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_A:
		this->player->PowerUp(); break;
	case DIK_LEFT:
		this->player->OnSpeedUp(DIR_LEFT); break;
	case DIK_RIGHT:
		this->player->OnSpeedUp(DIR_RIGHT); break;
	default:
		break;
	}
}

void CPlayScene::OnKeyPress(int keyCode)
{
	switch (keyCode)
	{
	default:
		break;
	}	
}

void CPlayScene::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_LEFT:
	case DIK_RIGHT:
		this->player->OnStopSpeedUp(); break;
	default:
		break;
	}
}
