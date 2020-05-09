#include "CreateMoveHook.h"
#include "HackCore.h"
#include "BannyHop.h"
#include "LegitBot.h"
#include <Windows.h>
#include "menu.h"

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	HacksF::BannyHop::Do(UCMD);
	if (GetAsyncKeyState(VK_MENU))  //if ALT				TODO:	ADD CUSTOM AIM BUTTON  (and use it in InputSystem. Without Windows.h)
		HacksF::LegitBot::DoAim(UCMD);
	if (Menu::is_open)
		UCMD->Buttons &= ~IN_ATTACK;
	return false;
}