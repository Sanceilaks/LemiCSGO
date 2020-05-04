#pragma once
#include "HookManager.h"

#include <MinHook.h>
#include "UserCmd.h"
#include "HackCore.h"

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

bool HookManager::Init()
{
	auto CreateMoveTarget = reinterpret_cast<void*>(get_virtual(HackCore::GetInstance()->ClientMode, 24));

	if (MH_Initialize() != MH_OK)
	{
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(CreateMoveTarget, &Hooks::CreateMove::hook, reinterpret_cast<void**>(&this->CreateMoveOriginal)) != MH_OK) {
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	HackCore::AddLog("Hook setuped");

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