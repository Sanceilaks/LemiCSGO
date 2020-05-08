#include "BannyHop.h"
#include "HackCore.h"
#include "CSPlayer.h"
#include "Settings.h"

void HacksF::BannyHop::Do(CUserCmd* cmd)
{
	if (!CoreSettings::Get().GetHackSettings()->BHOP->isActive)
		return;
	CSPlayer* LocalPlayer = CSPlayer::GetLocalPlayer();
	
	if (!LocalPlayer)
		return;

	if (cmd->Buttons & IN_JUMP && !(LocalPlayer->flags() & ON_GRAUND))
	{
		cmd->Buttons &= ~IN_JUMP;
	}
}