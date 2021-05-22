#pragma once

#include <vector>
#include "mesh.h"
#include <runner/src/include/PointMesh.h>
#include <runner/src/include/Circule.h>



class Pipe {
	unsigned int N;
	std::vector<Circule*> listSegmentCircule;

public:
	Pipe(unsigned int N);

	~Pipe();

	void removeFirst();

	void drawPipe(Mesh& obj, std::vector<Color>& v);

	void addCircule(const Point& center, float size, const Vector& axis, const Vector& v);
};
