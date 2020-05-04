#pragma once
#include <cstdint>

class IEntityList
{
public:
	void* GetEntityByIndex(int n)
	{
		using orig_fn = void* (__thiscall*)(IEntityList*, int);
		return (*(orig_fn**)this)[3](this, n);
	}
	void* GetEntityByHandle(uintptr_t handle)
	{
		using orig_fn = void* (__thiscall*)(IEntityList*, uintptr_t);
		return (*(orig_fn**)this)[4](this, handle);
	}
};