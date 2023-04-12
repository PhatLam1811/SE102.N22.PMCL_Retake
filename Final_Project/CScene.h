#pragma once

#include <Windows.h>

using namespace std;

class CScene
{
protected:
	int id;
	wstring filePath;
	
	// vector<CGameObject*> gameObjs;

public:
	CScene(int sceneId, wstring filePath)
	{
		this->id = sceneId;
		this->filePath = filePath;
	}

	virtual void GetCamPos(float &cameraX, float &cameraY) { /* cameraX = 0f; cameraY = 0f; */ }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
