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
	
	vector<CBaseGameObject*> gameObjects;

public:
	CScene(int sceneId, wstring filePath)
	{
		this->id = sceneId;
		this->filePath = filePath;

		// a scene will always have its camera 
		CCamera* mainCamera = new CCamera();
		this->gameObjects.push_back(mainCamera);
	}

	virtual void GetCamPos(float &cameraX, float &cameraY) { cameraX = 0.0f; cameraY = 0.0f; }
	virtual void Load() = 0;
	virtual void AddGameObject(int objectId, float x, float y) = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
