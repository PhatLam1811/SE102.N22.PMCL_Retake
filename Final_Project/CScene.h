#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "CBaseGameObject.h"
#include "CCamera.h"

using namespace std;

class CScene
{
protected:
	int id;
	wstring filePath;
	
	CCamera* camera;

	vector<CBaseGameObject*> gameObjects;

public:
	CScene(int sceneId, wstring filePath)
	{
		this->id = sceneId;
		this->filePath = filePath;

		// a scene will always have its camera 
		this->camera = new CCamera(0.0f, 0.0f);
	}

	virtual void GetCamPos(float& camX, float& camY) { this->camera->GetPosition(camX, camY); }
	virtual void SetCamPos(float camX, float camY) { this->camera->SetPosition(camX, camY); }
	
	virtual void Load() = 0;
	virtual void AddGameObject(int objectId, float x, float y) = 0;
	virtual void AddGameObject(CBaseGameObject* gameObject) = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
