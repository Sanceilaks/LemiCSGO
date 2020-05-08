#pragma once
#include "UserCmd.h"
#include "HooksInclude.h"
#include "CPanel.h"
#include "CSurface.h"
#include <d3d9.h>

namespace Hooks
{
	namespace CreateMove
	{
		using func = bool(_stdcall*)(float, CUserCmd*);
		static bool __fastcall hook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD);
	};

	namespace PaintTraverse 
	{
		using func = void(__thiscall*)(CPanel*, unsigned int, bool, bool);
		static void __stdcall hook(unsigned int Panel, bool ForceRepaint, bool AllowForce);
	};

	namespace EndScane
	{
		using func = long(__stdcall*)(IDirect3DDevice9*);
		static long __stdcall hook(IDirect3DDevice9* device);
	};

	namespace Reset
	{
		using func = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		static long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
	}

	namespace LockCursor
	{
		using func = void(__thiscall*)(CSurface*);
		static void __stdcall hook();
	}
}

class HookManager
{
public:
	HookManager()
	{

	}

	Hooks::CreateMove::func CreateMoveOriginal = nullptr;
	Hooks::PaintTraverse::func PaintTreverseOriginal = nullptr;
	Hooks::EndScane::func EndScaneOriginal = nullptr;
	Hooks::Reset::func ResetOriginal = nullptr;
	Hooks::LockCursor::func LockCursorOriginal = nullptr;

	bool Init();
	void RemoveAllHook();
};
