#pragma once
#include <string>
#include <Windows.h>
#include "IInclude.h"
#include "HookManager.h"
#include "Render.h"
#include "top.h"
#include <d3d9.h>


class Globals
{
public:
	bool MenuIsOpen = false;
};

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
	CPanel* Panel = nullptr;
	CSurface* Surface = nullptr;
	IDirect3DDevice9* DirectX = nullptr;
	CIInput* InputSystem = nullptr;

	HookManager* MyHookManager;
	CTools* Tools;
	Render* CRender;
	Globals* MyGlobals = new Globals(); //why no?

	bool isWork = true;
	bool isInit = false;
	std::string version = "0.1";
	static HackCore* GetInstance();
	static void AddLog(const char* val);

	void CoreInit();
	void CoreUnload(HMODULE hModule);
};

