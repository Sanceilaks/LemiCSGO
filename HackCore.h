#pragma once
#include <string>
#include <Windows.h>
#include "IInclude.h"
#include "HookManager.h"

class HackCore
{
	bool Work = true;
	
	static HackCore* instance;
	HackCore()
	{

	}
	~HackCore()
	{
		delete(this->Tools);
		delete(this);
	}
public:

	IBaseClientDll* BaseClientDll = nullptr;
	CEngineClient* EngineClient = nullptr;
	IEntityList* ClientEntityList = nullptr;
	IClientMode* ClientMode = nullptr;

	HookManager* MyHookManager;
	CTools* Tools;

	bool isWork = true;
	bool isInit = false;
	std::string version = "0.1";
	static HackCore* GetInstance();
	static void AddLog(const char* val);

	void CoreInit();
	void CoreUnload(HMODULE hModule);
};

