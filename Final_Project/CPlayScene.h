#pragma once

#include "CScene.h"
#include "CInputManager.h"

class CPlayScene : public CScene, public IKeyInputProcessable
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

	// Inherited via OnInputCallback
	virtual void OnKeyDown(BYTE* keyStates) override;
	virtual void OnKeyPress(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;
};
