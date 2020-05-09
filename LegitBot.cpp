#include "LegitBot.h"
#include "HackCore.h"
#include "HackUtils.h"
#include "CSPlayer.h"
#include "QAngle.h"


Math::CVector CalcAngle(Math::CVector src, Math::CVector dst)
{
	Math::CVector vAngle;
	Math::CVector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	vAngle.x = (float)(atan((delta.z + 64.06f) / hyp) * 57.295779513082f);
	vAngle.y = (float)(atan(delta.y / delta.x) * 57.295779513082f);
	vAngle.z = 0.0f;

	if (delta.x >= 0.0)
		vAngle.y += 180.0f;

	return vAngle;
}

CSPlayer* HacksF::LegitBot::GetClosestEnemyToCrosshair()
{
	CSPlayer* LocalPlayer = CSPlayer::GetLocalPlayer();

	if (!LocalPlayer || LocalPlayer->isAlive()) return NULL;

	float closestdis = 99999;
	int closestdistindex = -1;

	for (size_t i = 0; i <= HackCore::GetInstance()->EngineClient->GetMaxClients(); i++)
	{
		CSPlayer* ent = (CSPlayer*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(i);
		if (!ent) continue;

		if (ent->isAlive() || ent == LocalPlayer || ent->dormant()) continue; //filter

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
	//Math::CVector NewAngles = HacksF::HGame::GetEntityBone(enemy, ECSPlayerBones::head_0);


	ang = CalcAngle(LocalPlayer->GetEyePos(), HacksF::HGame::GetEntityBone(enemy, ECSPlayerBones::head_0));

	Math::NormalizeCVector(ang);
	Math::ClampAngles(ang);
	
	if (ucmd->ViewAngles != ang)
		ucmd->ViewAngles = ang;

	HackCore::GetInstance()->EngineClient->SetViewAngles(ucmd->ViewAngles);
	//ucmd->AimDirection = HacksF::HGame::GetEntityBone(enemy, ECSPlayerBones::head_0);
	//LocalPlayer->set_angles(HacksF::HGame::GetEntityBone(enemy, ECSPlayerBones::head_0));

}