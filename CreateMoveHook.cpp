#include "CreateMoveHook.h"
#include "HackCore.h"
#include "BannyHop.h"
#include <Windows.h>
#include "menu.h"

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	HacksF::BannyHop::Do(UCMD);

	if (Menu::is_open)
		UCMD->Buttons &= ~IN_ATTACK;
	return false;
}