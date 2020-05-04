#pragma once
#include "ClientClass.h"

class IBaseClientDll
{
public:
	ClientClass* GetAllClasses() {
		using original_fn = ClientClass * (__thiscall*)(IBaseClientDll*);
		return (*(original_fn**)this)[8](this);
	}
}; extern IBaseClientDll* BaseClientDll;