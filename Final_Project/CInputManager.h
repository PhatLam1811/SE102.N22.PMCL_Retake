#pragma once
class CInputManager
{
private:
	static CInputManager* instance;

	CInputManager();
	CInputManager(const CInputManager*);

public:
	static CInputManager* GetInstance();

	~CInputManager();
};

