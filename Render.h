#pragma once
#include "CSurface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"

enum font_flags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

namespace fonts
{
	extern unsigned long wotermarkfont;
};

class Render
{
	bool isInit = false;
public:
	void Init(CSurface* core);
};
