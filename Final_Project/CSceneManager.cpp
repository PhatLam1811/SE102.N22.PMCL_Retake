#include "CSceneManager.h"
#include "CPlayScene.h"

CSceneManager* CSceneManager::instance = nullptr;

CSceneManager* CSceneManager::GetInstance()
{
	if (instance == nullptr) instance = new CSceneManager();
	return instance;
}

CSceneManager::CSceneManager() { this->currentSceneId = -1; }
CSceneManager::CSceneManager(const CSceneManager*) { this->currentSceneId = -1; }
CSceneManager::~CSceneManager() { delete this; }

int CSceneManager::GetCurrentSceneId() { return this->currentSceneId; }
void CSceneManager::SetCurrentSceneId(int id) { this->currentSceneId = id; }
CScene* CSceneManager::GetCurrentScene() { return this->scenes[currentSceneId]; }

CScene* CSceneManager::GetScene(int sceneId)
{
	return this->scenes[sceneId];
}

void CSceneManager::AddScene(int sceneId, wstring filePath)
{
	CScene* newScene = new CPlayScene(sceneId, filePath);
	this->scenes[sceneId] = newScene;
}

void CSceneManager::ChangeScene(int nextSceneId)
{
	this->currentSceneId = nextSceneId;

	// unload scene...
}
