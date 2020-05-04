#include "BannyHop.h"
#include "HackCore.h"
#include "CBaseEntity.h"

void BannyHop::Do(CUserCmd* cmd)
{
	CBaseEntity* LocalPlayer = (CBaseEntity*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(HackCore::GetInstance()->EngineClient->GetLocalPlayerIndex());
	
	if (!LocalPlayer)
		return;

	if (cmd->Buttons & IN_JUMP && !(LocalPlayer->flags() & ON_GRAUND))
	{
		cmd->Buttons &= ~IN_JUMP;
	}
}