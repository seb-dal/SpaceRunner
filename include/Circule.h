#pragma once

#include <vector>
#include "mesh.h"

class Circule {
public:
	unsigned int N;
	Point** listPoints;

	Circule(unsigned int N, const Point& center, float size, const Vector& axis, const Vector& v);

	~Circule();

	Point& get(unsigned int i);
};
