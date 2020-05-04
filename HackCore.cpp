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

void HackCore::AddLog(const char* text)
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
	this->ClientEntityList = (IEntityList*)this->Tools->GetInterface("client_panorama.dll", "VClientEntityList003");

	printf("BaseClientDll = %u\n", reinterpret_cast<DWORD>(this->BaseClientDll));
	printf("EngineClient = %u\n", reinterpret_cast<DWORD>(this->EngineClient));
	printf("ClientEntityList = %u\n", reinterpret_cast<DWORD>(this->ClientEntityList));

	do {
		this->ClientMode = **(IClientMode***)((*(uintptr_t**)this->BaseClientDll)[10] + 0x5);
	} while (!this->ClientMode);

	this->MyHookManager = new HookManager();

	this->MyHookManager->Init();

	this->isInit = !this->isInit;
}

void HackCore::CoreUnload(HMODULE hModule)
{
	if (!this->isInit)
		return;

	this->AddLog("bb");
	this->MyHookManager->RemoveAllHook();
	FreeConsole();
	FreeLibraryAndExitThread(hModule, TRUE);
}