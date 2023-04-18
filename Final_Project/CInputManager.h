#pragma once

#include <vector>
#include <dinput.h>

#include "CScene.h"
#include "GameDefine.h"

using namespace std;

class IKeyInputProcessable
{
public:
	virtual void OnKeyDown(BYTE* keyStates) = 0;
	virtual void OnKeyPress(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
};

class CInputManager
{
private:

	static CInputManager* instance;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	vector<IKeyInputProcessable*> keyProcessors;	// Key input concrete handlers (Scenes)
	//vector<void(CScene::*)(BYTE*)> onKeyDownCallBacks;

	CInputManager();
	CInputManager(const CInputManager*);

public:
	static CInputManager* GetInstance();
	
	void Init();

	void AssignKeyInputCallback(IKeyInputProcessable* processor);
	void UnAssignKeyInputCallback(IKeyInputProcessable* processor);
	
	void OnKeyDownCallback(BYTE* keyStates);
	void OnKeyPressCallback(int keyCode);
	void OnKeyUpCallback(int keyCode);
	
	//void AssignOnKeyDownCallbacks(void (CScene::*callback)(BYTE*));

	//void DetachOnKeyDownCallbacks(void (CScene::*callback)(BYTE*));

	//void InvokeOnKeyDownCallbacks(BYTE* keyState);

	void ProcessInput();

	~CInputManager();
};