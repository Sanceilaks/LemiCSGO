#pragma once
#include <cstdint>

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
		using orig_fn = int(__thiscall*)(CEngineClient*); //������������ �������. int - ��, ��� ��� �����. � ��������� ������� - ��� ��� ��� ���������
		//����������� ��������� ��������� �� ���� �����
		return (*(orig_fn**)this)[12](this); //��� ����� �������� ������ [12]. ��� �������� �������. ��� ��� ����� ��� ��������, � ��� �� ����� ����� � ���
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
};