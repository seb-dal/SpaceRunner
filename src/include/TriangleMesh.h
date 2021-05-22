#pragma once
#include <runner/src/include/PointMesh.h>

class PointMesh;
class TriangleMesh {
public:
	PointMesh* p1;
	PointMesh* p2;
	PointMesh* p3;

	TriangleMesh(PointMesh* p1, PointMesh* p2, PointMesh* p3);

	void draw(Mesh& obj);
};