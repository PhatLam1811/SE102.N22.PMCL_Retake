#include "CSceneManager.h"
#include "CPlayScene.h"

CSceneManager* CSceneManager::instance = nullptr;

CSceneManager* CSceneManager::GetInstance()
{
	if (instance == nullptr) instance = new CSceneManager();
	return instance;
}

CSceneManager::CSceneManager() { return; }
CSceneManager::CSceneManager(const CSceneManager*) { return; }
CSceneManager::~CSceneManager() { delete this; }

int CSceneManager::GetCurrentSceneId() { return currentSceneId; }
void CSceneManager::SetCurrentSceneId(int id) { currentSceneId = id; }
CScene* CSceneManager::GetCurrentScene() { return scenes[currentSceneId]; }

void CSceneManager::AddScene(int sceneId, wstring filePath)
{
	CScene* newScene = new CPlayScene(sceneId, filePath);
	this->scenes[sceneId] = newScene;
}

void CSceneManager::ChangeScene(int nextSceneId)
{
	currentSceneId = nextSceneId;

	// unload scene...
}
