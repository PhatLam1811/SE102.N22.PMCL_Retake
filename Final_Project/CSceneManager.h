#pragma once
#include <unordered_map>
#include <string>

#include "CScene.h"

using namespace std;

class CSceneManager
{
private:
	static CSceneManager* instance;

	unordered_map<int, CScene*> scenes;
	
	int currentSceneId;

	CSceneManager();
	CSceneManager(const CSceneManager*);

public:
	static CSceneManager* GetInstance();

	int GetCurrentSceneId();
	void SetCurrentSceneId(int id);

	size_t GetScenesCount() { return scenes.size(); }

	CScene* GetCurrentScene();
	CScene* GetScene(int sceneId);
	void AddScene(int sceneId, wstring scenePath); // play scene
	void ChangeScene(int nextSceneId);

	~CSceneManager();
};
