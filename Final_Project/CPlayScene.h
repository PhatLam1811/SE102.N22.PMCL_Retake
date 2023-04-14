#pragma once

#include "CScene.h"

class CPlayScene : public CScene
{
public:
	CPlayScene(int sceneId, wstring filePath);

	virtual void Load();
	virtual void Unload();
	virtual void Update(DWORD dt);
	virtual void Render();
};
