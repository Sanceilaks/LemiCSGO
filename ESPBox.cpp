#include "ESPBox.h"
#include "imgui/imgui.h"
#include "csgodraw.h"
#include "HackCore.h"
#include "CSPlayer.h"
#include "HackUtils.h"
#include "Settings.h"

void HacksF::ESPBox::Render()
{
	if (!CoreSettings::Get().GetHackSettings()->ESP->IsActive)
		return;

	if (!HackCore::GetInstance()->EngineClient->isInGame())
		return;
	
	ImDrawList* drawlist = ImGui::GetOverlayDrawList();
	

	for (size_t i = 0; i <= HackCore::GetInstance()->EngineClient->GetMaxClients() ; i++)
	{
		CSPlayer* ent = (CSPlayer*)HackCore::GetInstance()->ClientEntityList->GetEntityByIndex(i);
		if (!ent) continue;

		if (!ent->isAlive() || ent == CSPlayer::GetLocalPlayer() || ent->dormant()) continue; //filter
		
		if (!(ent->GetClientClass()->class_id == class_ids::ccsplayer)) continue; //filter too (only Player and bots)


		Math::CVector vOrigin = ent->GetOrigin();
		Math::CVector vHead = HacksF::HGame::GetEntityBone(ent, ECSPlayerBones::head_0);

		vHead += 15.0f;

		Math::CVector vScreenOrigin, vScreenHead;

		if (HacksF::HMath::WorldToScreen(vHead, vScreenHead) && HacksF::HMath::WorldToScreen(vOrigin, vScreenOrigin))
		{
			float h = abs(vScreenHead.y - vScreenOrigin.y);
			float w = h * 0.65f;

			float x1, x2, y1, y2;

			x1 = vScreenOrigin.x - w / 2;
			y1 = vScreenOrigin.y;
			x2 = x1 + w;
			y2 = -h + y1;


			draw::csgod::DXDraw::RenderOutlinedRect(drawlist, x1, y1, x2, y2, Utils::Color(CoreSettings::Get().GetHackSettings()->ESP->BoxColor));

			auto health = ent->GetHealth();

			auto offset = (std::min)(static_cast<float>(health) / ent->GetMaxHealth(), 1.f);
			int green = int(health * 2.55f);
			int red = 255 - green;
			draw::csgod::DXDraw::RenderRectFilled(drawlist, x1 - 5.f, y1 - 1.f, x1 - 2.f, y2 + 1.f, Utils::Color(0, 0, 0));
			if (health > 0)
				draw::csgod::DXDraw::RenderRectFilled(drawlist, x1 - 4.f, y1, x1 - 3.f, y1 - offset * (y1 - y2), Utils::Color(red, green, 0));

		}
	}
	
	//draw::csgod::DXDraw::RenderRectFilled(drawlist, 500, 500, 600, 600, Color(10, 10, 10, 255));
}