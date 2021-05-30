#include "runner/include/Pipeline_Part_CMR.h"

#include <omp.h>

const float Pipeline_Part_CMR::NB_POINTS = 100;

Pipeline_Part_CMR::Pipeline_Part_CMR(
	const Point* prevPrev, const Point* prev, const Point* start, const Point* end, const Point* after,
	const Vector& v, const float sizePipe, const unsigned int N, std::vector<Color>& mats, const float NumPart
) :sizePipe(sizePipe), NumPart(NumPart) {
	this->prev = prev;
	this->start = start;
	this->end = end;
	this->after = after;

	// create all points
	listPoints = std::vector<Point>(NB_POINTS + 2);

	listPoints[0] = (
		Point(Utility::CatMullRom(Vector(*prevPrev), Vector(*prev), Vector(*start), Vector(*end), (float)(NB_POINTS - 1) / (float)NB_POINTS))
		+ Point(Utility::CatMullRom(Vector(*prev), Vector(*start), Vector(*end), Vector(*after), 0))
		) / 2;

	//#pragma omp parallel for
	for (int i = 1; i < listPoints.size(); i++) {
		listPoints[i] = Point(Utility::CatMullRom(Vector(*prev), Vector(*start), Vector(*end), Vector(*after), (float)(i - 1) / (float)NB_POINTS));
	}

	//std::cout << Point(Utility::CatMullRom(Vector(*prevPrev), Vector(*prev), Vector(*start), Vector(*end), 1)) << " " << Point(Utility::CatMullRom(Vector(*prev), Vector(*start), Vector(*end), Vector(*after), 0)) << std::endl;
	// create all normals pipe
	Utility::buildPerpendicularVect(listPoints, this->v, v);

	// build circules Pipe 
	PipeBuilder builder = PipeBuilder(N);
	builder.allocCircule(listPoints.size());

	//#pragma omp parallel for
	for (int i = 0; i < listPoints.size() - 1; i++) {
		builder.addCircule(
			i,
			listPoints[i],
			sizePipe,
			Utility::getVector(
				listPoints[i],
				listPoints[i + 1]
			),
			this->v[i]
		);
	}
	builder.addCircule(
		listPoints.size() - 1,
		listPoints[listPoints.size() - 1],
		sizePipe,
		Utility::getVector(
			listPoints[listPoints.size() - 2],
			listPoints[listPoints.size() - 1]
		),
		this->v[listPoints.size() - 1]
	);

	// draw mesh
	if (true) {
		fragment = new Mesh(GL_TRIANGLES);
		builder.drawPipe(*fragment, mats);
	}
	else {
		fragment = new Mesh(GL_LINE);
		Utility::drawLineWithVec(*fragment, listPoints, this->v);
	}
}




Pipeline_Part_CMR::~Pipeline_Part_CMR() {
	for (int i = 0; i < list_colision.size(); i++) {
		delete list_colision[i];
	}

	fragment->release();
	delete fragment;
}





Mesh* Pipeline_Part_CMR::get() { return fragment; }

std::vector<Box*>& Pipeline_Part_CMR::getColision() { return list_colision; }

std::vector<Point>& Pipeline_Part_CMR::getPoints() { return listPoints; }

std::vector<Vector>& Pipeline_Part_CMR::getV() { return v; }





void Pipeline_Part_CMR::genColision(Pipeline* pipe, unsigned int nbColision, Point pmin, Point pmax) {
	if (nbColision > 0) {

		float pp = (NB_POINTS - 4) / ((float)(nbColision));
		list_colision = std::vector<Box*>(nbColision);

		for (int i = 0; i < list_colision.size(); i++) {
			float a = Utility::randf(0, 360);
			float p = Utility::randf(pp * i, pp * (i + 1));

			Box* c = new Box(pmin, pmax);

			c->T = Utility::modelOnPipe(
				pipe,
				NumPart * NB_POINTS + p,
				sizePipe * -1,
				a,
				Vector(-1, 0, 0)
			);
			c->T = c->T(Scale(0.5));

			list_colision[i] = c;
		}
	}
}
