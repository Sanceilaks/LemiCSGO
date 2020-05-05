#pragma once
#include "CBaseEntity.h"
#include "HackCore.h"

class CSPlayer : public CBaseEntity
{
public:
	static CSPlayer* GetLocalPlayer()
	{
		return (CSPlayer*)(CBaseEntity*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(HackCore::GetInstance()->EngineClient->GetLocalPlayerIndex());
	}

	Math::CVector GetEyePos()
	{
		return this->GetOrigin() + this->GetViewOffset();
	}

	NETVAR("DT_BasePlayer", "m_aimPunchAngle", GetAimPunch, Math::CVector*);
	NETVAR("DT_BasePlayer", "m_viewPunchAngle", GetViewPunch, Math::CVector*);
	NETVAR("DT_BasePlayer", "m_iHealth", GetHealth, int);
	NETVAR("DT_BasePlayer", "m_lifeState", isAlive, bool);
};

