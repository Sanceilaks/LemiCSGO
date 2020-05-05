#pragma once
#include "CBaseEntity.h"
#include "HackCore.h"

class BaseCombatWeapon : public CBaseEntity
{
	CBaseEntity* GetOwner()
	{
		return (CBaseEntity*)HackCore::GetInstance()->ClientEntityList->GetEntityByHandle(this->GetOwnerHandle());
	}
	const char* GetName()
	{
		using orig_fn = const char* (__thiscall*)(BaseCombatWeapon*);
		return (*(orig_fn**)this)[378](this);
	}

	NETVAR("DT_BaseEntity", "m_OwnerEntity", GetOwnerId, int);
};