#pragma once
#include <string>
#include <Windows.h>
#include "IInclude.h"

class HackCore
{
	bool isInit = false;
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
	CTools* Tools;

	std::string version = "0.1";
	static HackCore* GetInstance();
	static void AddLog(std::string text);

	void CoreInit();
	void CoreUnload(HMODULE hModule);
};

