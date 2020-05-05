#include "EndScane.h"
#include <iostream>
#include <Windows.h>
#include "Imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "menu.h"
#include "ESPBox.h"

extern IMGUI_API LRESULT   ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace HacksF
{
	inline void DrawHack()
	{
		ESPBox::Render();
	}
}

namespace original
{
	static WNDPROC wnd_proc = nullptr;
}

LRESULT STDMETHODCALLTYPE user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	if (GetAsyncKeyState(VK_INSERT) & 0x1) {
		Menu::ToggleMenu();
	}
	if (ImGui_ImplDX9_WndProcHandler(window, message_type, w_param, l_param) && Menu::is_open) {
		return 1l;
	}

	return CallWindowProc(original::wnd_proc, window, message_type, w_param, l_param);
};


void __stdcall MyHooks::EndScane(IDirect3DDevice9* device)
{
	if (!isInit) {
		auto game_hwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		if (game_hwnd != NULL) {
			original::wnd_proc = reinterpret_cast<WNDPROC>(
				SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, LONG_PTR(user_wndproc))
				);

			ImGui_ImplDX9_Init(game_hwnd, device);

			ImGui::GetIO().IniFilename = nullptr;

			isInit = true;
		}
	}
	else 
	{
		ImGui_ImplDX9_NewFrame();

		if (Menu::is_open)
		{
			Menu::Draw();
		}
		else 
		{
			
		}
		HacksF::DrawHack();
		ImGui::Render();
	}
}