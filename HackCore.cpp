#include "HackCore.h"
#include <iostream>
#include <Windows.h>

HackCore* HackCore::instance = nullptr;

HackCore* HackCore::GetInstance()
{
	if (instance == nullptr)
		instance = new HackCore();
	return instance;
}

void HackCore::AddLog(std::string text)
{
	std::cout << text << "\n";
}

void HackCore::CoreInit()
{
	if (this->isInit)
		return;

	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);

	this->Tools = new CTools();
	
	//getting interfaces (classes)
	this->BaseClientDll = (IBaseClientDll*) this->Tools->GetInterface("client_panorama.dll", "VClient018");
	this->EngineClient = (CEngineClient*)this->Tools->GetInterface("engine.dll", "VEngineClient014");
	this->isInit = !this->isInit;
}

void HackCore::CoreUnload(HMODULE hModule)
{
	if (!this->isInit)
		return;

	//this->AddLog("bb");
	FreeConsole();
	FreeLibraryAndExitThread(hModule, TRUE);
}