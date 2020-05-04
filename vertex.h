#pragma once
#include "vector.h"
struct vertex {
	vertex() {}
	vertex(const CVector& pos, const CVector& coord = CVector(0, 0)) {
		position = pos;
		tex_coord = coord;
	}
	void initialize(const CVector& pos, const CVector& coord = CVector(0, 0)) {
		position = pos;
		tex_coord = coord;
	}

	CVector	position;
	CVector	tex_coord;
};