#include "CreateMoveHook.h"
#include "HackCore.h"
#include "BannyHop.h"
#include <Windows.h>

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	HacksF::BannyHop::Do(UCMD);
	return false;
}