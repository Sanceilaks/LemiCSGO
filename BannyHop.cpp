#include "BannyHop.h"
#include "HackCore.h"
#include "CSPlayer.h"


void HacksF::BannyHop::Do(CUserCmd* cmd)
{
	
	CSPlayer* LocalPlayer = CSPlayer::GetLocalPlayer();
	
	if (!LocalPlayer)
		return;

	if (cmd->Buttons & IN_JUMP && !(LocalPlayer->flags() & ON_GRAUND))
	{
		cmd->Buttons &= ~IN_JUMP;
	}
}