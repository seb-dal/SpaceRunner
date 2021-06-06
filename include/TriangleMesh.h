#pragma once
#include <runner/include/PointMesh.h>

class PointMesh;
class TriangleMesh {
public:
	PointMesh* p1;
	PointMesh* p2;
	PointMesh* p3;

	bool textcord = false;
	vec2 t1, t2, t3;

	TriangleMesh(PointMesh* p1, PointMesh* p2, PointMesh* p3);

	void setTextCoord(vec2& tr1, vec2& tr2, vec2& tr3, bool swapAxes);

	void draw(Mesh& obj);
};