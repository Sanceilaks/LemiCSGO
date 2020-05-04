#pragma once

#pragma region includes

#include <Windows.h>
#include <iostream>

#include "UserCmd.h"

#pragma endregion

#pragma region protos

typedef void* (*Interface)(const char* _Name, int Return);
typedef void* (*InstantiateInterface)();
//typedef void(__thiscall* PaintTraverse)(void*, unsigned int, bool, bool);

//typedef bool(__thiscall* CreateMove)(void*, float, CUserCmd*);

#pragma endregion


class CTools
{
public:
	//быстрый, но сложный бля понимания способ
	virtual void* GetInterface(const char* _Module, const char* _Interface)
	{
		Interface TempInterface = (Interface)GetProcAddress(GetModuleHandle(_Module), "CreateInterface");

		return (void*)TempInterface(_Interface, 0);
	}
	//тоже быстрый, но ещё больше непонятных штук
	void* CaptureInterface(const char* mod, const char* iface) {
		using fn_capture_iface_t = void* (*)(const char*, int*);
		auto fn_addr = (fn_capture_iface_t)GetProcAddress(GetModuleHandleA(mod), "CreateInterface");

		auto iface_addr = fn_addr(iface, nullptr);
		printf("found %s at 0x%p\n", iface, fn_addr(iface, nullptr));

		return iface_addr;
	}

}; extern CTools* Tools;

template< typename Function > Function EmulateVirtual(void* _VMT, int Index)
{
	void*** _TVMT = (void***)_VMT;

	void** VMT = *_TVMT;

	void* _Address = VMT[Index];

	return (Function)(_Address);
}