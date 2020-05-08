#include "PaintTreverseHook.h"
#include "fnv.h"
#include "HackCore.h"

void __stdcall MyHooks::MyPaintTreverseHook(unsigned int panel, bool ForceRepaint, bool AllowForce)
{
	//HackCore::GetInstance()->Panel->CurrentPanel = panel;


	//auto panel_to_draw = fnv::hash(HackCore::GetInstance()->Panel->get_panel_name(panel));

	//switch (panel_to_draw) {
	//case fnv::hash("MatSystemTopPanel"):

	//	//render::draw_text_string(10, 10, render::fonts::watermark_font, "csgo-cheat", false, color::white(255));

	//	///menu::toggle();
	//	//menu::render();

	//	break;

	////case fnv::hash("FocusOverlayPanel"):
	////	HackCore::GetInstance()->Panel->set_keyboard_input_enabled(panel, variables::menu::opened);
	////	HackCore::GetInstance()->Panel->set_mouse_input_enabled(panel, variables::menu::opened);
	////	break;
	//}
}

