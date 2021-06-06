#pragma once
#include <src/gKit/vec.h>
#include <src/gKit/color.h>
#include <vector>
#include <runner/include/Utility.h>
#include <runner/include/TriangleMesh.h>

class TriangleMesh;
class PointMesh {
public:
	PointMesh() {};
	PointMesh(Point& coord);

	Vector getNormalMoy();

	void addTriangle(TriangleMesh* t);

	Point getPoint();

	void setTexCoord(float x, float y);
	void setTexCoord(vec2& tex);
	vec2 getTexCoord();

	Color getColor();
	void setColor(Color col);

	void clear();

	void draw(Mesh& obj);

private:
	Point p;

	bool tex_Ok = false;
	vec2 tex;

	bool c_ok = false;
	Color c;
	std::vector<TriangleMesh*> inTriangles;
};