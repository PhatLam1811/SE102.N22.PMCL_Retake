#include "CInputManager.h"
#include "CGraphicManager.h"
#include "Utils.h"

CInputManager* CInputManager::instance = nullptr;

CInputManager* CInputManager::GetInstance()
{
	if (instance == nullptr) instance = new CInputManager();
	return instance;
}

void CInputManager::Init()
{
	HINSTANCE hInstance = CGraphicManager::GetInstance()->GetHInstance();
	HWND hWnd = CGraphicManager::GetInstance()->GetWndHandler();
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&this->di, NULL);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = this->di->CreateDevice(GUID_SysKeyboard, &this->didv, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = this->didv->SetDataFormat(&c_dfDIKeyboard);

	hr = this->didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = this->didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = this->didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

CInputManager::CInputManager() { return; }
CInputManager::CInputManager(const CInputManager*) { return; }
CInputManager::~CInputManager() { delete this; }

void CInputManager::AssignKeyInputCallback(IKeyInputProcessable* processor)
{
	this->UnAssignKeyInputCallback(processor); // prevent duplicates
	this->keyProcessors.push_back(processor);
}

void CInputManager::UnAssignKeyInputCallback(IKeyInputProcessable* processor)
{
	this->keyProcessors.erase(
		remove(
		this->keyProcessors.begin(),
		this->keyProcessors.end(),
		processor),
		this->keyProcessors.end());
}

void CInputManager::OnKeyDownCallback(int keyCode)
{
	for (auto processor : this->keyProcessors)
	{
		processor->OnKeyDown(keyCode);
	}
}

void CInputManager::OnKeyPressCallback(int keyCode)
{
	for (auto processor : this->keyProcessors)
	{
		processor->OnKeyPress(keyCode);
	}
}

void CInputManager::OnKeyUpCallback(int keyCode)
{
	for (auto processor : this->keyProcessors)
	{
		processor->OnKeyUp(keyCode);
	}
}

bool CInputManager::IsKeyDown(int KeyCode)
{
	return (this->keyStates[KeyCode] & 0x80) > 0;
}

void CInputManager::ProcessKeyDown()
{
	if (this->IsKeyDown(DIK_A))
		this->OnKeyDownCallback(DIK_A);

	if (this->IsKeyDown(DIK_S))
		this->OnKeyDownCallback(DIK_S);
}

void CInputManager::ProcessInput()
{
	HRESULT hr;

	// Collect all key states first
	hr = this->didv->GetDeviceState(sizeof(this->keyStates), this->keyStates);

	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = this->didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	this->ProcessKeyDown();
	// this->OnKeyDownCallback(this->keyStates);
	// this->KeyState((BYTE*)&keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = this->didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = this->keyEvents[i].dwOfs;
		int KeyState = this->keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			this->OnKeyPressCallback(KeyCode);
		// keyHandler->OnKeyDown(KeyCode);
		else
			this->OnKeyUpCallback(KeyCode);
			// keyHandler->OnKeyUp(KeyCode);
	}
}