#pragma once

#include "CScene.h"

class CPlayScene : public CScene
{
private:
	bool isMarioLoaded;

public:
	CPlayScene(int sceneId, wstring filePath);

	// Inherited via CScene
	virtual void Load();
	virtual void AddGameObject(int objectId, float x, float y);
	virtual void Unload();
	virtual void Update(DWORD dt);
	virtual void Render();
};
