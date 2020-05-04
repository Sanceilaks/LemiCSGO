#pragma once

#pragma region includes

#include <Windows.h>
#include <iostream>
#include <vector>

#pragma endregion

#pragma region protos

typedef void* (*Interface)(const char* _Name, int Return);
typedef void* (*InstantiateInterface)();
//typedef void(__thiscall* PaintTraverse)(void*, unsigned int, bool, bool);

//typedef bool(__thiscall* CreateMove)(void*, float, CUserCmd*);

#pragma endregion


class CTools
{
public:
	//быстрый, но сложный бля понимания способ
	virtual void* GetInterface(const char* _Module, const char* _Interface)
	{
		Interface TempInterface = (Interface)GetProcAddress(GetModuleHandle(_Module), "CreateInterface");

		return (void*)TempInterface(_Interface, 0);
	}
	//тоже быстрый, но ещё больше непонятных штук
	void* CaptureInterface(const char* mod, const char* iface) {
		using fn_capture_iface_t = void* (*)(const char*, int*);
		auto fn_addr = (fn_capture_iface_t)GetProcAddress(GetModuleHandleA(mod), "CreateInterface");

		auto iface_addr = fn_addr(iface, nullptr);
		printf("found %s at 0x%p\n", iface, fn_addr(iface, nullptr));

		return iface_addr;
	}
    std::uint8_t* PatternScaner(const char* module_name, const char* signature) noexcept {
        const auto module_handle = GetModuleHandleA(module_name);

        if (!module_handle)
            return nullptr;

        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + std::strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;

                    if (*current == '?')
                        ++current;

                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(std::strtoul(current, &current, 16));
                }
            }
            return bytes;
        };

        auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
        auto nt_headers =
            reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

        auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto pattern_bytes = pattern_to_byte(signature);
        auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

        auto s = pattern_bytes.size();
        auto d = pattern_bytes.data();

        for (auto i = 0ul; i < size_of_image - s; ++i) {
            bool found = true;

            for (auto j = 0ul; j < s; ++j) {
                if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found)
                return &scan_bytes[i];
        }

        return nullptr;
    }
};

template< typename Function > Function EmulateVirtual(void* _VMT, int Index)
{
	void*** _TVMT = (void***)_VMT;

	void** VMT = *_TVMT;

	void* _Address = VMT[Index];

	return (Function)(_Address);
}