#pragma once
#include "imgui/imgui.h"
#include "HackCore.h"
#include "CustomUIModules.h"
#include "Settings.h"

namespace Menu
{
	namespace mywin
	{
		namespace Visual
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		};
	};
	static bool is_open = false;
	static void Draw()
	{
		ImGui::Begin("Hello", (bool*)0, ImVec2(300, 640), 0.3f, ImGuiWindowFlags_NoResize || ImGuiColorEditFlags_NoTooltip);
		if (ImGui::Button("Close")) HackCore::GetInstance()->MyGlobals->MenuIsOpen = !HackCore::GetInstance()->MyGlobals->MenuIsOpen;
		mywin::Visual::Draw();

		ImGui::End();
	}
	static void ToggleMenu()
	{
		HackCore::GetInstance()->MyGlobals->MenuIsOpen = !HackCore::GetInstance()->MyGlobals->MenuIsOpen;
		is_open = !is_open;
		switch (HackCore::GetInstance()->MyGlobals->MenuIsOpen)
		{
		case true:
			CustomUI::DrawCursorToggle();
			break;
		case false:
			CustomUI::DrawCursorToggle();
			break;
		}
	}
}