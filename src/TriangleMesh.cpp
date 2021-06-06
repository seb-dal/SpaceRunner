#include "runner/include/TriangleMesh.h"

TriangleMesh::TriangleMesh(PointMesh* p1, PointMesh* p2, PointMesh* p3) :p1(p1), p2(p2), p3(p3) {}

void TriangleMesh::setTextCoord(vec2& tr1, vec2& tr2, vec2& tr3, bool swapAxes) {
	t1 = (swapAxes) ? vec2(tr1.y, tr1.x) : vec2(tr1);
	t2 = (swapAxes) ? vec2(tr2.y, tr2.x) : vec2(tr2);
	t3 = (swapAxes) ? vec2(tr3.y, tr3.x) : vec2(tr3);
	textcord = true;
}

void TriangleMesh::draw(Mesh& obj) {
	if (textcord)
		obj.texcoord(t1);
	p1->draw(obj);

	if (textcord)
		obj.texcoord(t2);
	p2->draw(obj);

	if (textcord)
		obj.texcoord(t3);
	p3->draw(obj);
}




