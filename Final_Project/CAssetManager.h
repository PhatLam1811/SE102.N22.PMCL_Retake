#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>

#include "CSprite.h"

using namespace std;

class CAssetManager
{
private:
	static CAssetManager* instance;

	unordered_map<int, CTexture*> textures;
	unordered_map<int, CSprite*> sprites;

	CAssetManager();
	CAssetManager(const CAssetManager*);

public:
	static CAssetManager* GetInstance();

	void LoadAssets(wstring assetsPath);
	CTexture* LoadTexture(wstring texturePath);

	void AddTexture(int textureId, wstring filePath);

	void AddSprite(int spriteId, int left, int top, int right, int bottom, int textureId);
	CSprite* GetSprite(int spriteId);

	size_t GetTexturesCount() { return this->textures.size(); }
	size_t GetSpritesCount() { return this->sprites.size(); }
	
	void Clear();

	~CAssetManager();
};
