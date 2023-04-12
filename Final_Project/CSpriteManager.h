#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>

#include "CSprite.h"

using namespace std;

class CSpriteManager
{
private:
	static CSpriteManager* instance;

	unordered_map<int, CSprite*> sprites;

	CSpriteManager();
	CSpriteManager(const CSpriteManager*);

public:
	static CSpriteManager* GetInstance();

	void LoadAssets(wstring assetsFilePath);
	CSprite* GetSprite(int spriteId);
	void Clear();

	~CSpriteManager();
};
