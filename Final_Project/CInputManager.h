#pragma once

#include <vector>
#include <dinput.h>

#include "CScene.h"
#include "GameDefine.h"

using namespace std;

class IKeyInputProcessable
{
public:
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyPress(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
};

class CInputManager
{
private:

	static CInputManager* instance;

	LPDIRECTINPUT8       di = nullptr;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv = nullptr;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	vector<IKeyInputProcessable*> keyProcessors;	// Key input concrete handlers (Scenes)

	CInputManager();
	CInputManager(const CInputManager*);

public:
	static CInputManager* GetInstance();
	
	void Init();

	void AssignKeyInputCallback(IKeyInputProcessable* processor);
	void UnAssignKeyInputCallback(IKeyInputProcessable* processor);
	
	void OnKeyDownCallback(int keyCode);
	void OnKeyPressCallback(int keyCode);
	void OnKeyUpCallback(int keyCode);

	bool IsKeyDown(int KeyCode);
	void ProcessKeyDown();
	void ProcessInput();

	~CInputManager();
};