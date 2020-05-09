#pragma once
#include "imgui/imgui.h"
#include "HackCore.h"
#include "CustomUIModules.h"
#include "Settings.h"

#define ButtonSize ImVec2(80, 30)

namespace Menu
{
	enum WinButtons
	{
		AIM,
		VISUAL,
		SKIN,
		MISC,
		CONFIG
	};

	namespace mywin
	{
		namespace Visual
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::ColorEdit3("ESPBox color", CoreSettings::Get().GetHackSettings()->ESP->BoxColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs);
				ImGui::EndGroup();
			};
		};
		namespace Aim
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
		namespace Skins
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
		namespace Misc
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
		namespace Config
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
	};
	static int currentwin = VISUAL;
	static bool is_open = false;

	static void DrawCurrent()
	{
		switch (currentwin)
		{
		case AIM:
			mywin::Aim::Draw();
			break;
		case VISUAL:
			mywin::Visual::Draw();
			break;
		case SKIN:
			mywin::Skins::Draw();
			break;
		case MISC:
			mywin::Misc::Draw();
			break;
		case CONFIG:
			mywin::Config::Draw();
			break;
		}
	}

	static void Draw()
	{
		ImGui::Begin("Hello", (bool*)0, ImVec2(700, 340), 0.9f, ImGuiWindowFlags_NoResize);
		ImGui::SameLine();

		ImGui::BeginChild("###tabs", ImVec2(700, 40));
		ImGui::SameLine();
		//ImGui::Spacing();

		if (ImGui::Button("AIM", ButtonSize))		currentwin = AIM;
		ImGui::SameLine();
		//ImGui::Spacing();

		if (ImGui::Button("VISUAL", ButtonSize))	currentwin = VISUAL;
		ImGui::SameLine();
		//ImGui::Spacing();

		if (ImGui::Button("SKIN", ButtonSize))		currentwin = SKIN;
		ImGui::SameLine();
		//ImGui::Spacing();

		if (ImGui::Button("MISC", ButtonSize))		currentwin = MISC;
		//ImGui::Spacing();
		ImGui::SameLine();

		if (ImGui::Button("CONFIG", ButtonSize))	currentwin = CONFIG;
		//ImGui::Spacing();
		ImGui::SameLine();

		ImGui::EndChild();

		ImGui::Spacing();
		ImGui::Spacing();
		
		DrawCurrent();

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