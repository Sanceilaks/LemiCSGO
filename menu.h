#pragma once
#include "imgui/imgui.h"

namespace Menu
{
	static bool is_open = false;
	void Draw()
	{
		ImGui::Begin("Hello");
		if (ImGui::Button("Close")) is_open = !is_open;
		ImGui::End();
	}
}