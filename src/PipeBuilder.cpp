#include "runner/include/PipeBuilder.h"

#include <map>


PipeBuilder::PipeBuilder(unsigned int N) {
	this->N = N;
}

PipeBuilder::~PipeBuilder() {
	for (int i = 0; i < listSegmentCircule.size(); i++) {
		delete listSegmentCircule[i];
	}
	listSegmentCircule.clear();
}

void PipeBuilder::removeFirst() {
	delete listSegmentCircule[0];
	listSegmentCircule.erase(listSegmentCircule.begin());
}

static std::string namePoint(Point& p) {
	std::string a;
	a.append(std::to_string(p.x));
	a.append(" ");
	a.append(std::to_string(p.y));
	a.append(" ");
	a.append(std::to_string(p.z));
	return a;
}

static PointMesh* getOrCreate(Point& p, std::map<std::string, PointMesh*>& listp) {
	std::string name = namePoint(p);
	if (listp.find(name) != listp.end()) {
		return listp[name];
	}
	//#pragma omp critical
	{
		if (listp.find(name) == listp.end()) {
			PointMesh* pm = new PointMesh(p);
			listp[name] = pm;
			return pm;
		}
		else {
			return listp[name];
		}
	}
}

void PipeBuilder::drawPipe(Mesh& obj, std::vector<Color>& v) {
	std::map<std::string, PointMesh*> listPoint;
	std::vector<TriangleMesh*> listTriangle;

	//PRE-DRAW
	if (listSegmentCircule.size() > 0) {

		//#pragma omp parallel for
		for (int i = 1; i < listSegmentCircule.size(); i++) {
			Circule* c1 = listSegmentCircule[i - 1];
			Circule* c2 = listSegmentCircule[i];

			//#pragma omp parallel for
			for (int p = 0; p < N; p++) {

				PointMesh* p1 = getOrCreate(c2->get(p), listPoint);
				PointMesh* p2 = getOrCreate(c1->get(p), listPoint);
				PointMesh* p3 = getOrCreate(c1->get(p + 1), listPoint);
				PointMesh* p4 = getOrCreate(c2->get(p + 1), listPoint);

				TriangleMesh* t1 = new TriangleMesh(p1, p2, p3);
				TriangleMesh* t2 = new TriangleMesh(p1, p3, p4);

				listTriangle.push_back(t1); listTriangle.push_back(t2);


				p1->addTriangle(t1);
				p1->addTriangle(t2);

				p2->addTriangle(t1);

				p3->addTriangle(t1);
				p3->addTriangle(t2);

				p4->addTriangle(t2);


				p1->setColor(v.at(p % v.size()));
				p2->setColor(v.at(p % v.size()));
			}
		}
	}


	for (TriangleMesh* t : listTriangle) {
		t->draw(obj);
	}

	for (TriangleMesh* t : listTriangle) {
		delete t;
	}
	for (std::map<std::string, PointMesh*>::iterator it = listPoint.begin(); it != listPoint.end(); ++it) {
		delete it->second;
	}
}

void PipeBuilder::allocCircule(const unsigned int size) {
	listSegmentCircule.resize(size);
}

void PipeBuilder::addCircule(const Point& center, const float size, const Vector& axis, const Vector& v) {
	listSegmentCircule.push_back(new Circule(N, center, size, axis, v));
}

void PipeBuilder::addCircule(const unsigned int pos, const Point& center, float size, const Vector& axis, const Vector& v) {
	listSegmentCircule[pos] = new Circule(N, center, size, axis, v);
}
