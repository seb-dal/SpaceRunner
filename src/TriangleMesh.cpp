#include "runner/include/TriangleMesh.h"

TriangleMesh::TriangleMesh(PointMesh* p1, PointMesh* p2, PointMesh* p3) :p1(p1), p2(p2), p3(p3) {}

void TriangleMesh::draw(Mesh& obj) {
	p1->draw(obj);
	p2->draw(obj);
	p3->draw(obj);
}




