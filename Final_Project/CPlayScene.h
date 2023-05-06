#pragma once

#include "CMario.h"

#include "CScene.h"
#include "CInputManager.h"

class CPlayScene : public CScene, public IKeyInputHandler
{
private:
	CMario* player;

public:
	CPlayScene(int sceneId, wstring filePath);

	// Inherited via CScene
	virtual void Load() override;
	virtual void AddGameObject(CBaseGameObject* gameObject) override;
	virtual void Unload() override;
	virtual void Update(DWORD dt) override;
	virtual void Render() override;

	// Inherited via OnInputCallback
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyPress(int keyCode);
	virtual void OnKeyUp(int keyCode);
};
