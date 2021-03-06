#pragma once
#include "imgui/imgui.h"
#include "color.h"

namespace ImGuiHelp
{
	//��� � �������
	enum ImDrawCornerFlags_
	{
		ImDrawCornerFlags_TopLeft = 1 << 0, // 0x1
		ImDrawCornerFlags_TopRight = 1 << 1, // 0x2
		ImDrawCornerFlags_BotLeft = 1 << 2, // 0x4
		ImDrawCornerFlags_BotRight = 1 << 3, // 0x8
		ImDrawCornerFlags_Top = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,   // 0x3
		ImDrawCornerFlags_Bot = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,   // 0xC
		ImDrawCornerFlags_Left = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,    // 0x5
		ImDrawCornerFlags_Right = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight,  // 0xA
		ImDrawCornerFlags_All = 0xF     // In your function calls you may use ~0 (= all bits sets) instead of ImDrawCornerFlags_All, as a convenience
	};
}

namespace draw
{
	namespace csgod
	{
		namespace DXDraw
		{
			//������ ������ ����� (��� �� ����������)
			inline void RenderLine(ImDrawList* draw_list, float x1, float y1, float x2, float y2, Utils::Color col)
			{
				draw_list->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), col.GetU32());
			}
			inline void RenderOutlinedCricle(ImDrawList* draw_list, float x, float y, float radius, Utils::Color col = Utils::Color(0, 0, 0), int segments = 12)
			{
				draw_list->AddCircle(ImVec2(x, y), radius, col.GetU32());
			}
			/*inline void RenderText(ImDrawList* draw_list, const char* text, float x, float y, Color col, ImFont* font = arial, float font_size = 18.0f)
			{
				draw_list->AddText(font, font_size, ImVec2(x, y), col.GetU32(), text);
			}*/
			inline void RenderOutlinedRect(ImDrawList* draw_list, float x1, float y1, float x2, float y2, Utils::Color col = Utils::Color(0, 0, 0), float rounding = 0.0f, int rounding_corners_flags = ImGuiHelp::ImDrawCornerFlags_All)
			{
				draw_list->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), col.GetU32(), rounding, rounding_corners_flags);
			}
			inline void RenderRectFilled(ImDrawList* draw_list, float x1, float y1, float x2, float y2, Utils::Color col, float rounding = 0.0f, int rounding_corners_flags = ImGuiHelp::ImDrawCornerFlags_All)
			{
				draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col.GetU32(), rounding, rounding_corners_flags);
			}
		}
	};
}