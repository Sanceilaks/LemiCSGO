#pragma once
#include "UserCmd.h"
#include "HooksInclude.h"


namespace Hooks
{
	namespace CreateMove
	{
		using func = bool(_stdcall*)(float, CUserCmd*);
		static bool __fastcall hook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD);
	};
}

class HookManager
{
public:
	HookManager()
	{

	}

	Hooks::CreateMove::func CreateMoveOriginal = nullptr;
	bool Init();
	void RemoveAllHook();
};
