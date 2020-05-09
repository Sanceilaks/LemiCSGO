#pragma once
#include "CSPlayer.h"
#include "UserCmd.h"
/*
	TODO:
	LegitBot xd)
*/



namespace HacksF
{
	namespace LegitBot
	{
		CSPlayer* GetClosestEnemyToCrosshair();
		void DoAim(CUserCmd* ucmd);
	}
}