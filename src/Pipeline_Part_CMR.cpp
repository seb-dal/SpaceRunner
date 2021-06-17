#include "runner/include/Pipeline_Part_CMR.h"

const float Pipeline_Part_CMR::NB_POINTS = 100;


Pipeline_Part_CMR::Pipeline_Part_CMR(
	const Point* prevPrev, const Point* prev, const Point* start, const Point* end, const Point* after,
	const Vector& v, const float sizePipe, const unsigned int N, std::vector<Color>& mats, const float NumPart
) :sizePipe(sizePipe), NumPart(NumPart) {
	this->prev = prev;
	this->start = start;
	this->end = end;
	this->after = after;

	float NB_POINTS_FLOAT = NB_POINTS;
	// create all points
	listPoints = std::vector<Point>(NB_POINTS + 2);

	listPoints[0] = (
		Point(Utility::CatMullRom(*prevPrev, *prev, *start, *end, (NB_POINTS_FLOAT - 1.f) / NB_POINTS_FLOAT))
		+ Point(Utility::CatMullRom(*prev, *start, *end, *after, 0))
		) / 2;

	//#pragma omp parallel for
	int i;
	for (i = 1; i < listPoints.size(); i++) {
		listPoints[i] = Point(Utility::CatMullRom(*prev, *start, *end, *after, (float)(i - 1) / NB_POINTS_FLOAT));
	}

	//std::cout << Point(Utility::CatMullRom(Vector(*prevPrev), Vector(*prev), Vector(*start), Vector(*end), 1)) << " " << Point(Utility::CatMullRom(Vector(*prev), Vector(*start), Vector(*end), Vector(*after), 0)) << std::endl;
	// create all normals pipe
	Utility::buildPerpendicularVect(listPoints, this->v, v);

	// build circules Pipe 
	PipeBuilder builder = PipeBuilder(N);
	builder.allocCircule(listPoints.size());
	size_t size;
	//#pragma omp parallel for
	for (i = 0; i < listPoints.size() - 1; i++) {
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


	size = listPoints.size() - 1;
	builder.addCircule(
		size,
		listPoints[size],
		sizePipe,
		Utility::getVector(
			listPoints[size - 1],
			listPoints[size]
		),
		this->v[size]
	);

	// draw mesh
	fragment = new Mesh(GL_TRIANGLES);
	builder.drawPipe(*fragment, mats);
}




Pipeline_Part_CMR::~Pipeline_Part_CMR() {
	list_Obstacle.clear();
	list_Bonus.clear();

	v.clear();
	listPoints.clear();

	fragment->release();
	delete fragment;
}





Mesh* Pipeline_Part_CMR::get() { return fragment; }

std::vector<ObstacleObj*>& Pipeline_Part_CMR::getObstacles() { return list_Obstacle; }

std::vector<BonusObj*>& Pipeline_Part_CMR::getBonus() { return list_Bonus; }

std::vector<Point>& Pipeline_Part_CMR::getPoints() { return listPoints; }

std::vector<Vector>& Pipeline_Part_CMR::getV() { return v; }





void Pipeline_Part_CMR::genColision(MeshLoader& loader, Pipeline* pipe, unsigned int nbColision, unsigned int nbBonus) {
	unsigned int i;
	float pp, a, p;
	if (nbColision > 0) {

		pp = (NB_POINTS - 4) / ((float)(nbColision));
		//list_Obstacle = std::vector<ObstacleObj*>(nbColision);

		for (i = 0; i < nbColision; i++) {
			a = Utility::randf(0, 360);
			p = Utility::randf(pp * i, pp * (i + 1));

			Transform T = Utility::modelOnPipe(
				pipe,
				NumPart * NB_POINTS + p,
				sizePipe * 0.8,
				a
			);

			//list_Obstacle[i] = new ObstacleObj(loader, T);
			list_Obstacle.push_back(new ObstacleObj(loader, T));
		}
	}
	if (nbBonus > 0) {
		pp = (NB_POINTS - 4) / ((float)(nbBonus));
		//list_Bonus = std::vector<BonusObj*>(nbBonus);

		for (i = 0; i < nbBonus; i++) {
			a = Utility::randf(0, 360);
			p = Utility::randf(pp * i, pp * (i + 1));

			Transform T = Utility::modelOnPipe(
				pipe,
				NumPart * NB_POINTS + p,
				sizePipe * 1.6,
				a
			);

			//list_Bonus[i] = new BonusObj(loader, T);
			list_Bonus.push_back(new BonusObj(loader, T));
		}
	}
}
