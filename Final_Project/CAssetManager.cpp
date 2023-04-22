#include <fstream>

#include "CAssetManager.h"
#include "CConfigManager.h"
#include "CGraphicManager.h"
#include "GameDefine.h"
#include "Utils.h"

// Singleton
CAssetManager* CAssetManager::instance = nullptr;

CAssetManager* CAssetManager::GetInstance()
{
	if (instance == nullptr) instance = new CAssetManager();
	return instance;
}

CAssetManager::CAssetManager() { return; }
CAssetManager::CAssetManager(const CAssetManager*) { return; }
CAssetManager::~CAssetManager() { delete this; }

void CAssetManager::LoadAssets(wstring assetsPath)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetsPath);

	ifstream f;
	f.open(assetsPath);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: CConfigManager::GetInstance()->ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: CConfigManager::GetInstance()->ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetsPath);
}

CTexture* CAssetManager::LoadTexture(wstring texturePath)
{
	ID3D10Resource* pD3D10Resource = nullptr;
	ID3D10Texture2D* tex = nullptr;

	// Retrieve image information first 
	D3DX10_IMAGE_INFO imageInfo;
	HRESULT hr = D3DX10GetImageInfoFromFile(texturePath.c_str(), NULL, &imageInfo, NULL);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10GetImageInfoFromFile failed for  file: %s with error: %d\n", texturePath, hr);
		return NULL;
	}

	D3DX10_IMAGE_LOAD_INFO info;
	ZeroMemory(&info, sizeof(D3DX10_IMAGE_LOAD_INFO));
	info.Width = imageInfo.Width;
	info.Height = imageInfo.Height;
	info.Depth = imageInfo.Depth;
	info.FirstMipLevel = 0;
	info.MipLevels = 1;
	info.Usage = D3D10_USAGE_DEFAULT;
	info.BindFlags = D3DX10_DEFAULT;
	info.CpuAccessFlags = D3DX10_DEFAULT;
	info.MiscFlags = D3DX10_DEFAULT;
	info.Format = imageInfo.Format;
	info.Filter = D3DX10_FILTER_NONE;
	info.MipFilter = D3DX10_DEFAULT;
	info.pSrcInfo = &imageInfo;

	// Loads the texture into a temporary ID3D10Resource object
	hr = D3DX10CreateTextureFromFile(CGraphicManager::GetInstance()->GetDirect3DDevice(),
		texturePath.c_str(),
		&info,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texturePath, hr);
		return NULL;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
	pD3D10Resource->Release();

	if (!tex) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return NULL;
	}

	//
	// Create the Share Resource View for this texture 
	// 	   
	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;

	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	CGraphicManager::GetInstance()->GetDirect3DDevice()->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

	DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texturePath);

	return new CTexture(tex, gSpriteTextureRV);
}

void CAssetManager::AddTexture(int textureId, wstring filePath)
{
	this->textures[textureId] = this->LoadTexture(filePath);
}

CTexture* CAssetManager::GetTexture(int textureId) { return this->textures[textureId]; }

void CAssetManager::AddSprite(int spriteId, int left, int top, int right, int bottom, int textureId)
{
	if (this->textures[textureId] == nullptr)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", textureId);
		return;
	}

	CSprite* sprite = new CSprite(spriteId, left, top, right, bottom, this->textures[textureId]);
	this->sprites[spriteId] = sprite;
}

CSprite* CAssetManager::GetSprite(int spriteId) { return this->sprites[spriteId]; }

void CAssetManager::Clear()
{
	for (auto x : this->sprites)
	{
		CSprite* s = x.second;
		delete s;
	}

	this->sprites.clear();
}
