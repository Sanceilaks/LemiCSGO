#pragma once
#include "imgui/imgui.h"
#include "HackCore.h"

namespace Menu
{
	static bool is_open = false;
	static void Draw()
	{
		ImGui::Begin("Hello");
		if (ImGui::Button("Close")) is_open = !is_open;
		ImGui::End();
	}
	static void ToggleMenu()
	{
		is_open = !is_open;
		switch (is_open)
		{
		case true:
			ImGui::GetIO().MouseDrawCursor = true;
			HackCore::GetInstance()->InputSystem->enable_input(false);
			break;
		case false:
			ImGui::GetIO().MouseDrawCursor = false;
			HackCore::GetInstance()->InputSystem->enable_input(true);
			break;
		}
	}
}