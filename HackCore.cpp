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
	this->Panel = (CPanel*)this->Tools->GetInterface("vgui2.dll", "VGUI_Panel009");
	this->Surface = (CSurface*)this->Tools->GetInterface("vguimatsurface.dll", "VGUI_Surface031");
	this->InputSystem = (CIInput*)this->Tools->GetInterface("inputsystem.dll", "InputSystemVersion001");

	printf("{CORE} BaseClientDll = %u\n", reinterpret_cast<DWORD>(this->BaseClientDll));
	printf("{CORE} EngineClient = %u\n", reinterpret_cast<DWORD>(this->EngineClient));
	printf("{CORE} ClientEntityList = %u\n", reinterpret_cast<DWORD>(this->ClientEntityList));
	printf("{CORE} CPanel = %u\n", reinterpret_cast<DWORD>(this->Panel));
	printf("{CORE} CSurface = %u\n", reinterpret_cast<DWORD>(this->Surface));
	printf("{CORE} InputSystem = %u\n", reinterpret_cast<DWORD>(this->InputSystem));

	do {
		this->ClientMode = **(IClientMode***)((*(uintptr_t**)this->BaseClientDll)[10] + 0x5);
	} while (!this->ClientMode);

	this->DirectX = **(IDirect3DDevice9***)(Tools->PatternScaner("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	printf("{CORE} ClientMode = %u\n", reinterpret_cast<DWORD>(this->ClientMode));
	printf("{CORE} DXAPI = %u\n", reinterpret_cast<DWORD>(this->DirectX));

	this->MyHookManager = new HookManager();

	this->MyHookManager->Init();

	//this->CRender->Init(this->Surface);

	this->isInit = !this->isInit;
}

void HackCore::CoreUnload(HMODULE hModule)
{
	if (!this->isInit)
		return;

	this->AddLog("{CORE} bb");
	this->MyHookManager->RemoveAllHook();
	FreeConsole();
	FreeLibraryAndExitThread(hModule, TRUE);
}