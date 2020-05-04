#include "CreateMoveHook.h"
#include "HackCore.h"
#include "BannyHop.h"

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	BannyHop::Do(UCMD);
	return false;
}