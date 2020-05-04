#pragma once
#include <Windows.h>
#include "Netvars.h"

#define ON_GRAUND		(1 << 0)


class CBaseEntity
{
public:
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
	//bool setup_bones(matrix_t* out, int max_bones, int mask, float time) {
	//	if (!this)
	//		return false;

	//	using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
	//	return (*(original_fn**)animating())[13](animating(), out, max_bones, mask, time);
	//}
	//model_t* model() {
	//	using original_fn = model_t * (__thiscall*)(void*);
	//	return (*(original_fn**)animating())[8](animating());
	//}
	void update() {
		using original_fn = void(__thiscall*)(CBaseEntity*);
		(*(original_fn**)this)[218](this);
	}
	//int draw_model(int flags, uint8_t alpha) {
	//	using original_fn = int(__thiscall*)(void*, int, uint8_t);
	//	return (*(original_fn**)animating())[9](animating(), flags, alpha);
	//}
	//void set_angles(vec3_t angles) {
	//	using original_fn = void(__thiscall*)(void*, const vec3_t&);
	//	static original_fn set_angles_fn = (original_fn)((DWORD)utilities::pattern_scan("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
	//	set_angles_fn(this, angles);
	//}
	//void set_position(vec3_t position) {
	//	using original_fn = void(__thiscall*)(void*, const vec3_t&);
	//	static original_fn set_position_fn = (original_fn)((DWORD)utilities::pattern_scan("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
	//	set_position_fn(this, position);
	//}

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
	NETVAR("DT_BaseEntity", "m_hOwnerEntity", owner_handle, unsigned long);
	NETVAR("DT_CSPlayer", "m_flSimulationTime", simulation_time, float);
	//NETVAR("DT_BasePlayer", "m_vecOrigin", origin, vec3_t);
	//NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", view_offset, vec3_t);
	NETVAR("DT_CSPlayer", "m_iTeamNum", team, int);
	NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool);
	NETVAR("DT_CSPlayer", "m_nSurvivalTeam", survival_team, int);
	NETVAR("DT_CSPlayer", "m_flHealthShotBoostExpirationTime", health_boost_time, float);
};