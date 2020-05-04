#include "EndScane.h"
#include <iostream>
#include <Windows.h>
#include "Imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "Render.h"
#include "menu.h"

extern IMGUI_API LRESULT   ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace original
{
	static WNDPROC wnd_proc = nullptr;
}

LRESULT STDMETHODCALLTYPE user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	if (GetAsyncKeyState(VK_INSERT) & 0x1) {
		Menu::is_open = !Menu::is_open;
	}
	if (ImGui_ImplDX9_WndProcHandler(window, message_type, w_param, l_param) && Menu::is_open) {
		return 1l;
	}

	return CallWindowProc(original::wnd_proc, window, message_type, w_param, l_param);
};

void __stdcall MyHooks::EndScane(IDirect3DDevice9* device)
{
	static bool initialised = false;
	if (!initialised) {
		auto game_hwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		if (game_hwnd != NULL) {
			original::wnd_proc = reinterpret_cast<WNDPROC>(
				SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, LONG_PTR(user_wndproc))
				);

			ImGui_ImplDX9_Init(game_hwnd, device);

			initialised = true;
		}
	}
	else {
		ImGui_ImplDX9_NewFrame();

		if (Menu::is_open) {
			Menu::Draw();
		}
		else 
		{
			/*do nothing, menu is closed*/
		}

		ImGui::Render();
	}
}