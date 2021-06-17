#include "runner/include/PointMesh.h"

PointMesh::PointMesh(Point& coord) :p(coord) { }

Vector PointMesh::getNormalMoy() {
	Vector res;
	int i;
	for (i = 0; i < inTriangles.size(); i++) {
		res = res + Utility::perpendicular_Vector_Triangle(
			Vector(inTriangles[i]->p1->getPoint()),
			Vector(inTriangles[i]->p2->getPoint()),
			Vector(inTriangles[i]->p3->getPoint())
		);
	}
	return normalize(res);
}



void PointMesh::addTriangle(TriangleMesh* t) { inTriangles.push_back(t); }



Point PointMesh::getPoint() { return p; }



void PointMesh::setTexCoord(float x, float y) { setTexCoord(vec2(x, y)); }



void PointMesh::setTexCoord(vec2& tex) { this->tex = vec2(tex); tex_Ok = true; }



vec2 PointMesh::getTexCoord() { return tex; }



Color PointMesh::getColor() { return c; }



void PointMesh::setColor(Color col) { c = col; c_ok = true; }



void PointMesh::clear() { inTriangles.clear(); }



void PointMesh::draw(Mesh& obj) {
	if (c_ok)
		obj.color(c);

	if (!inTriangles.empty())
		obj.normal(getNormalMoy());

	if (tex_Ok)
		obj.texcoord(tex);

	obj.vertex(p);
}

