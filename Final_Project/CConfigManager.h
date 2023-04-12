#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class CConfigManager
{
private:
	static CConfigManager* instance;

	CConfigManager();
	CConfigManager(const CConfigManager*);

public:
	static CConfigManager* GetInstance();

	void ParseSection_SETTINGS(string line, int& initialSceneId);
	void ParseSection_SCENES(string line, int& sceneId, wstring& scenePath);
	void ParseSection_TEXTURES(string line);
	void ParseSection_SPRITES(string line);
	void ParseSection_ANIMATIONS(string line);
	void ParseSection_ASSETS(string line);
	void ParseSection_OBJECTS(string line);

	~CConfigManager();
};

