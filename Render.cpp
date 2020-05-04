#include "Render.h"

unsigned long fonts::wotermarkfont;

//void Render::Init(CSurface* core)
//{
//	if (this->isInit)
//		return;
//
//	fonts::wotermarkfont = core->font_create();
//	core->set_font_glyph(fonts::wotermarkfont, "Tahoma", 12, 500, 0, 0, font_flags::fontflag_dropshadow);
//	
//	printf("{CORE} Render initialized!");
//	this->isInit = true;
//}