#pragma once
#include <src/gKit/vec.h>
#include <src/gKit/color.h>
#include <vector>
#include <runner/src/include/Utility.h>
#include <runner/src/include/TriangleMesh.h>

class TriangleMesh;
class PointMesh {
public:
	PointMesh() {};
	PointMesh(Point& coord);

	Vector getNormalMoy();

	void addTriangle(TriangleMesh* t);

	Point getPoint();
	Color getColor();
	void setColor(Color col);

	void draw(Mesh& obj);

private:
	Point p;
	Color c;
	std::vector<TriangleMesh*> inTriangles;
};