#pragma once
#include <Windows.h>
#include "Netvars.h"
#include "vector.h"
#define ON_GRAUND		(1 << 0)


class CBaseEntity
{

public:
	template<class Y>
	inline Y GetFiledValue(int offset)
	{
		return *(Y*)((DWORD)this + offset);
	}

	template<class Y>
	inline Y* GetFiledPointer(int offset)
	{
		return (Y*)((DWORD)this + offset);
	}
	void* Animating() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}
	void* Networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}
	int index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)Networkable())[10](Networkable());
	}
	bool isPlayer() {
		using original_fn = bool(__thiscall*)(CBaseEntity*);
		return (*(original_fn**)this)[157](this);
	}
	bool isWeapon() {
		using original_fn = bool(__thiscall*)(CBaseEntity*);
		return (*(original_fn**)this)[165](this);
	}
	bool setup_bones(Math::matrix3x4_t* out, int max_bones, int mask, float time) {
		if (!this)
			return false;

		using original_fn = bool(__thiscall*)(void*, Math::matrix3x4_t*, int, int, float);
		return (*(original_fn**)Animating())[13](Animating(), out, max_bones, mask, time);
	}
	//model_t* model() {
	//	using original_fn = model_t * (__thiscall*)(void*);
	//	return (*(original_fn**)animating())[8](animating());
	//}
	void update() {
		using original_fn = void(__thiscall*)(CBaseEntity*);
		(*(original_fn**)this)[218](this);
	}
	int draw_model(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn**)Animating())[9](Animating(), flags, alpha);
	}
	void set_angles(Math::CVector angles) {
		using original_fn = void(__thiscall*)(void*, const Math::CVector&);
		static original_fn set_angles_fn = (original_fn)((DWORD) IU::Memory::PatternScaner("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
		set_angles_fn(this, angles);
	}
	void set_position(Math::CVector position) {
		using original_fn = void(__thiscall*)(void*, const Math::CVector&);
		static original_fn set_position_fn = (original_fn)((DWORD)IU::Memory::PatternScaner("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
		set_position_fn(this, position);
	}

	void SetModelIndex(int index) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[75](this, index);
	}

	void net_pre_data_update(int update_type) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)Networkable())[6](Networkable(), update_type);
	}

	void net_release() {
		using original_fn = void(__thiscall*)(void*);
		return (*(original_fn**)Networkable())[1](Networkable());
	}

	int net_set_destroyed_on_recreate_entities() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)Networkable())[13](Networkable());
	}

	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
	OFFSET(bool, dormant, 0xED);
	NETVAR("DT_BaseEntity", "m_hOwnerEntity", GetOwnerHandle, unsigned long);
	NETVAR("DT_CSPlayer", "m_flSimulationTime", GetSimulationTime, float);
	NETVAR("DT_BasePlayer", "m_vecOrigin", GetOrigin, Math::CVector);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", GetViewOffset, Math::CVector);
	NETVAR("DT_CSPlayer", "m_iTeamNum", GetTeam, int);
	NETVAR("DT_BaseEntity", "m_bSpotted", GetSpotted, bool);
	NETVAR("DT_CSPlayer", "m_nSurvivalTeam", SurvivalTeam, int);
	NETVAR("DT_CSPlayer", "m_flHealthShotBoostExpirationTime", GetHealtBhoostTime, float);
};