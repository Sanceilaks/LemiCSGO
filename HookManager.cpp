#pragma once
#include "HookManager.h"
#include <MinHook.h>
#include "UserCmd.h"
#include "HackCore.h"



unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

bool HookManager::Init()
{
	auto CreateMoveTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->ClientMode, 24));
	auto PaintTreverseTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->Panel, 41));
	auto EndScaneTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->DirectX, 42));
	auto ResetTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->DirectX, 16));
	auto LockCursorTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->Surface, 67));


	if (MH_Initialize() != MH_OK)
	{
		printf("failed to initialize MH_Initialize.\n");
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(CreateMoveTarget, &Hooks::CreateMove::hook, reinterpret_cast<void**>(&this->CreateMoveOriginal)) != MH_OK) {
		printf("failed to initialize CreateMove (outdated index?)\n");
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(PaintTreverseTarget, &Hooks::PaintTraverse::hook, reinterpret_cast<void**>(&this->PaintTreverseOriginal)) != MH_OK) {
		printf("failed to initialize PaintTreverse hook (outdated index?)\n");
		throw std::runtime_error("failed to initialize PaintTreverse hook (outdated index?)");
		return false;
	}

	if (MH_CreateHook(EndScaneTarget, &Hooks::EndScane::hook, reinterpret_cast<void**>(&this->EndScaneOriginal)) != MH_OK) {
		printf("failed to initialize EndScane (outdated index?)\n");
		throw std::runtime_error("failed to initialize EndScane (outdated index?)");
		return false;
	}

	if (MH_CreateHook(ResetTarget, &Hooks::Reset::hook, reinterpret_cast<void**>(&this->ResetOriginal)) != MH_OK) {
		printf("failed to initialize Reset (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_CreateHook(LockCursorTarget, &Hooks::LockCursor::hook, reinterpret_cast<void**>(&this->LockCursorOriginal)) != MH_OK) {
		printf("failed to initialize LockCursor (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	HackCore::GetInstance()->AddLog("{CORE} Hooks initialized!");

	return true;
}

void HookManager::RemoveAllHook()
{
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}

bool __fastcall Hooks::CreateMove::hook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	HackCore::GetInstance()->MyHookManager->CreateMoveOriginal(FrameTime, UCMD);
	return MyHooks::MyCreateMoveHook(ecx, edx, FrameTime, UCMD);
}

void __stdcall Hooks::PaintTraverse::hook(unsigned int panel, bool ForceRepaint, bool AllowForce)
{
	MyHooks::MyPaintTreverseHook(panel, ForceRepaint, AllowForce);
	HackCore::GetInstance()->MyHookManager->PaintTreverseOriginal(HackCore::GetInstance()->Panel, panel, ForceRepaint, AllowForce);
}

long __stdcall Hooks::EndScane::hook(IDirect3DDevice9* device)
{
	MyHooks::EndScane(device);
	return HackCore::GetInstance()->MyHookManager->EndScaneOriginal(device);
}
long __stdcall Hooks::Reset::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	long hr = HackCore::GetInstance()->MyHookManager->ResetOriginal(device, pPresentationParameters);
	MyHooks::Reset(device, pPresentationParameters, hr);
	return hr;
}

void __stdcall Hooks::LockCursor::hook()
{
	if (!MyHooks::MyLockCursor())
		HackCore::GetInstance()->MyHookManager->LockCursorOriginal(HackCore::GetInstance()->Surface);
}