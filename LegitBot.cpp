#include "LegitBot.h"
#include "HackCore.h"
#include "HackUtils.h"
#include "CSPlayer.h"
#include "QAngle.h"


Math::CVector CalcAngle(Math::CVector src, Math::CVector dst)
{
	auto ret = Math::CVector();
	Math::CVector delta = src - dst;
	double hyp = delta.Length2D();
	ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
	ret.x = (atan(delta.z / hyp) * 57.295779513082f);
	ret.z = 0.f;

	if (delta.x >= 0.f)
		ret.y += 180.f;
	return ret;
}

CSPlayer* HacksF::LegitBot::GetClosestEnemyToCrosshair()
{
	CSPlayer* LocalPlayer = CSPlayer::GetLocalPlayer();

	if (!LocalPlayer || !LocalPlayer->isAlive()) return NULL;

	float closestdis = 99999;
	int closestdistindex = -1;

	for (size_t i = 0; i <= HackCore::GetInstance()->EngineClient->GetMaxClients(); i++)
	{
		CSPlayer* ent = (CSPlayer*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(i);
		if (!ent) continue;

		if (!ent->isAlive() || ent == LocalPlayer || ent->dormant()) continue; //filter

		if (!(ent->GetClientClass()->class_id == class_ids::ccsplayer)) continue; //filter too (only Player and bots)

		if (ent->GetTeam() == LocalPlayer->GetTeam()) continue;

		float currentdist = LocalPlayer->GetDistance(ent);

		if (!(currentdist < closestdis)) continue;

		closestdis = currentdist;
		closestdistindex = i;

	}

	if (closestdistindex == -1) return NULL;

	return (CSPlayer*)(CBaseEntity*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(closestdistindex);
}

void HacksF::LegitBot::DoAim(CUserCmd* ucmd)
{
	if (!HackCore::GetInstance()->EngineClient->isInGame()) return;
	CSPlayer* enemy = GetClosestEnemyToCrosshair();
	if (!enemy) return;

	CSPlayer* LocalPlayer = CSPlayer::GetLocalPlayer();
	if (!LocalPlayer || LocalPlayer->isAlive()) return;

	Math::QAngle ang = ucmd->ViewAngles;

	ang = CalcAngle(LocalPlayer->GetEyePos(), HacksF::HGame::GetEntityBone(enemy, ECSPlayerBones::head_0));

	Math::ClampAngles(ang);
	
	if (ucmd->ViewAngles != ang)
		ucmd->ViewAngles = ang;

	HackCore::GetInstance()->EngineClient->SetViewAngles(ucmd->ViewAngles);

}