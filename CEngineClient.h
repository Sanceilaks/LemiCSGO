#pragma once
#include <cstdint>
#include "QAngle.h"
#include "VMatrix.h"

struct player_info_t {
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};



class CEngineClient
{
public:
	int GetLocalPlayerIndex()
	{
		using orig_fn = int(__thiscall*)(CEngineClient*); //оригинальная функция. int - то, что она вернёт. В следующих скобках - это что она принимает
		//Обязательно принимает указатель на свой класс
		return (*(orig_fn**)this)[12](this); //тут будет меняться только [12]. Это смещение функции. Впр тут будут все смещения, а так их можно найти в иде
	}
	int GetPlayerIndexByUUID(int user_id)
	{
		using orig_fn = int(__thiscall*)(CEngineClient*, int);
		return (*(orig_fn**)this)[9](this, user_id);
	}
	void ExecuteClientCmd(const char* exec)
	{
		using orig_fn = void(__thiscall*)(CEngineClient*, const char*);
		return (*(orig_fn**)this)[108](this, exec);
	}

	//i_net_channel* get_net_channel_info() {
	//	using original_fn = i_net_channel * (__thiscall*)(CEngineClient*);
	//	return (*(original_fn**)this)[78](this);
	//}
	void GetPlayerInfo(int index, player_info_t* info) {
		using original_fn = void(__thiscall*)(CEngineClient*, int, player_info_t*);
		return (*(original_fn**)this)[8](this, index, info);
	}
	void GetScreenSize(int& width, int& height) {
		using original_fn = void(__thiscall*)(CEngineClient*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}
	bool isInGame() {
		using original_fn = bool(__thiscall*)(CEngineClient*);
		return (*(original_fn**)this)[26](this);
	}
	bool isConnected() {
		using original_fn = bool(__thiscall*)(CEngineClient*);
		return (*(original_fn**)this)[27](this);
	}
	void SetViewAngles(Math::CVector& angles) {
		using original_fn = void(__thiscall*)(CEngineClient*, Math::CVector&);
		return (*(original_fn**)this)[19](this, angles);
	}

	int GetMaxClients()
	{
		return IU::Memory::call_virtual<int(__thiscall*)(void*)>(this, 20)(this);
	}

	void get_view_angles(Math::CVector& angles) {
		return IU::Memory::call_virtual<void(__thiscall*)(void*, Math::QAngle&)>(this, 18)(this, angles);
	}

	const Math::VMatrix& WorldToScreenMatrix()
	{
		return IU::Memory::call_virtual<const Math::VMatrix & (__thiscall*)(void*)>(this, 37)(this);
	}

	bool isTakingScreenshot() {
		using original_fn = bool(__thiscall*)(CEngineClient*);
		return (*(original_fn**)this)[92](this);
	}

	const char* GetLevelName() {
		using original_fn = const char* (__thiscall*)(CEngineClient*);
		return (*(original_fn**)this)[53](this);
	}

	float GetLastTimeStamp()
	{
		return IU::Memory::call_virtual<float(__thiscall*)(void*)>(this, 14)(this);
	}
};