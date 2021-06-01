#include "runner/include/PointMesh.h"

PointMesh::PointMesh(Point& coord) :p(coord) {}

Vector PointMesh::getNormalMoy() {
	Vector res;
	for (int i = 0; i < inTriangles.size(); i++) {
		res = res + Utility::perpendicular_Vector_Triangle(
			Vector(inTriangles[i]->p1->getPoint()),
			Vector(inTriangles[i]->p2->getPoint()),
			Vector(inTriangles[i]->p3->getPoint())
		);
	}
	return normalize(res);
}

void PointMesh::addTriangle(TriangleMesh* t) {
	//#pragma omp critical
	{
		inTriangles.push_back(t);
	}
}

Point PointMesh::getPoint() { return p; }

Color PointMesh::getColor() { return c; }

void PointMesh::setColor(Color col) { c = col; }

void PointMesh::clear() {
	inTriangles.clear();
}

void PointMesh::draw(Mesh& obj) {
	obj.color(c);
	if (!inTriangles.empty())
		obj.normal(getNormalMoy());
	obj.vertex(p);
}
