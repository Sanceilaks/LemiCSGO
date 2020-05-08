#pragma once
#include "vertex.h"
#include "vector2d.h"

class CSurface {
public:
	void SetDrawingColor(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[15](this, r, g, b, a);
	}

	void PlaySound(const char* sound_path) {
		using original_fn = void(__thiscall*)(CSurface*, const char*);
		return (*(original_fn**)this)[82](this, sound_path);
	}

	void SetTextColor(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[25](this, r, g, b, a);
	}

	//void draw_polygon(int n, vertex* vertice, bool clip_vertices = true) {
	//	using original_fn = void(__thiscall*)(CSurface*, int, vertex*, bool);
	//	return (*(original_fn**)this)[106](this, n, vertice, clip_vertices);
	//}
	void DrawFilledRectangle(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[16](this, x, y, x + w, y + h);
	}
	void SetTexture(int id) {
		using original_fn = void(__thiscall*)(CSurface*, int);
		return (*(original_fn**)this)[38](this, id);
	}
	inline void DrawTexturedRectangle(int x, int y, int w, int h) {
		typedef void(__thiscall* original_fn)(void*, int, int, int, int);
		return (*(original_fn**)this)[41](this, x, y, w, h);
	}
	void SetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall) {
		using original_fn = void(__thiscall*)(CSurface*, int, const unsigned char*, int, int, int, bool);
		return (*(original_fn**)this)[37](this, id, rgba, wide, tall, 0, false);
	}
	int CreateNewTextureId(bool procedural = false) {
		using original_fn = int(__thiscall*)(CSurface*, bool);
		return (*(original_fn**)this)[43](this, procedural);
	}
	void DrawOutlinedRect(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[18](this, x, y, x + w, y + h);
	}
	void DrawLine(int x1, int y1, int x2, int y2) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[19](this, x1, y1, x2, y2);
	}
	void DrawTextFont(unsigned long font) {
		using original_fn = void(__thiscall*)(CSurface*, unsigned long);
		return (*(original_fn**)this)[23](this, font);
	}
	void DrawTextPos(int x, int y) {
		using original_fn = void(__thiscall*)(CSurface*, int, int);
		return (*(original_fn**)this)[26](this, x, y);
	}
	void DrawRenderText(const wchar_t* text, int textLen) {
		using original_fn = void(__thiscall*)(CSurface*, const wchar_t*, int, int);
		return (*(original_fn**)this)[28](this, text, textLen, 0);
	}
	unsigned long FontCreate() {
		using original_fn = unsigned int(__thiscall*)(CSurface*);
		return (*(original_fn**)this)[71](this);
	}
	void SetFontGlyph(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) {
		using original_fn = void(__thiscall*)(CSurface*, unsigned long, const char*, int, int, int, int, int, int, int);
		return (*(original_fn**)this)[72](this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall) {
		using original_fn = void(__thiscall*)(CSurface*, unsigned long, const wchar_t*, int&, int&);
		return (*(original_fn**)this)[79](this, font, text, wide, tall);
	}

	void SetClipRect(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[147](this, x, y, w, h);
	}

	void DrawFilledRectFade(int x, int y, int w, int h, unsigned int alpha1, unsigned int alpha2, bool is_horizontal) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int, unsigned int, unsigned int, bool);
		return (*(original_fn**)this)[123](this, x, y, w, h, alpha1, alpha2, is_horizontal);
	}

	void DrawColoredText(unsigned long font, int x, int y, int red, int green, int blue, int alpha, const char* text) {
		using original_fn = void(__thiscall*)(CSurface*, unsigned long, int, int, int, int, int, int, const char*);
		return (*(original_fn**)this)[163](this, font, x, y, red, green, blue, alpha, text);
	}

	void GetScreenSize(int& width, int& height) {
		using original_fn = void(__thiscall*)(CSurface*, int&, int&);
		return (*(original_fn**)this)[44](this, std::ref(width), std::ref(height));  //width, height
	}

	//void draw_textured_polygon(int vertex_count, vertex* ver, bool clip_vertices = true) {
	//	using original_fn = void(__thiscall*)(CSurface*, int, vertex*, bool);
	//	return (*(original_fn**)this)[106](this, vertex_count, ver, clip_vertices);
	//}

	void DrawOutlinedCircle(int x, int y, int radius, int segments) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[103](this, x, y, radius, segments);
	}

	void DrawSetTextureFile(int texture_id, const char* texture_name, int hardware_filter, bool force_reload = 0) {
		using original_fn = void(__thiscall*)(CSurface*, int, const char*, int, bool);
		return (*(original_fn**)this)[36](this, texture_id, texture_name, hardware_filter, force_reload);
	}

	bool isTextureIdValid(int texture_id) {
		using original_fn = bool(__thiscall*)(CSurface*, int);
		return (*(original_fn**)this)[42](this, texture_id);
	}

	void SurfaceGetCursorPos(int& x, int& y) {
		using original_fn = void(__thiscall*)(CSurface*, int&, int&);
		return (*(original_fn**)this)[100](this, std::ref(x), std::ref(y));  //x, y
	}

	Math::CVector2D SurfaceGetCursorPos() {
		int x;
		int y;
		using original_fn = void(__thiscall*)(CSurface*, int&, int&);
		(*(original_fn**)this)[100](this, std::ref(x), std::ref(y));
		return Math::CVector2D(x, y);
	}

	void DrawTexturedRect(int x, int y, int width, int height) {
		using original_fn = void(__thiscall*)(CSurface*, int, int, int, int);
		return (*(original_fn**)this)[41](this, x, y, width, height);
	}

	//void LockCursor()
	//{
	//	using orig_fn = void(__thiscall*)(CSurface*);
	//	return (*(orig_fn**)this)[67](this);
	//}

	void UnlockCursor()
	{
		using orig_fn = void(__thiscall*)(CSurface*);
		return (*(orig_fn**)this)[66](this);
	}
};