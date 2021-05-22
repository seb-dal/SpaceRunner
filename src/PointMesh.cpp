#include "runner/src/include/PointMesh.h"

PointMesh::PointMesh(Point& coord) :p(coord) {}

Vector PointMesh::getNormalMoy() {
	Vector res;
	for (TriangleMesh* t : inTriangles) {
		res = res + Utility::perpendicular_Vector_Triangle(
			Vector(t->p1->getPoint()),
			Vector(t->p2->getPoint()),
			Vector(t->p3->getPoint())
		);
	}
	return normalize(res);
}

void PointMesh::addTriangle(TriangleMesh* t) {
	inTriangles.push_back(t);
}

Point PointMesh::getPoint() { return p; }

Color PointMesh::getColor() { return c; }

void PointMesh::setColor(Color col) { c = col; }

void PointMesh::draw(Mesh& obj) {
	obj.color(c);
	if (!inTriangles.empty())
		obj.normal(getNormalMoy());
	obj.vertex(p);
}
