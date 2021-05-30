#include "runner/include/Pipeline.h"

Pipeline::Pipeline(int sizePipe, unsigned int N) :sizePipe(sizePipe), N(N) {
	Obstacle = read_mesh("runner/data/Piece3.obj");
	group = Obstacle.groups();

	float L = 8.0f;
	float X = (float)N / L;
	for (float i = 0; i < X; i++) {
		float C = (i / X) * M_PI * 2.f;
		/*Material col = Material(
		Color(
		std::cos(C),
		std::cos(C + (2.0f / 3.0f) * M_PI),
		std::cos(C + (4.0f / 3.0f) * M_PI)
		)
		);*/
		mats.push_back(
			Color(
				0.5 * std::cos(C / 2),
				0,//std::cos(C),
				std::cos(C / 2)
			)
		);
	}

	listesPointsCourbures.push_back(new Point(-20 * sizePipe, -20 * sizePipe, -20 * sizePipe));
	listesPointsCourbures.push_back(new Point(-10 * sizePipe, -10 * sizePipe, -10 * sizePipe));
	listesPointsCourbures.push_back(new Point(0, 0, 0));
	listesPointsCourbures.push_back(new Point(10 * sizePipe, 10 * sizePipe, 10 * sizePipe));

	v = Vector(1, -1, 1);

	for (int i = 0; i < 20; i++) {
		addNewPart();
	}
}

Pipeline::~Pipeline() {
	for (int i = 0; i < parts.size(); i++) {
		delete parts.at(i);
	}

	for (int i = 0; i < listesPointsCourbures.size(); i++) {
		delete listesPointsCourbures.at(i);
	}

	mats.clear();
}




void Pipeline::addNewPart() {
	listesPointsCourbures.push_back(new Point(
		listesPointsCourbures.at(listesPointsCourbures.size() - 1)->x + sizePipe * 20.f,
		listesPointsCourbures.at(listesPointsCourbures.size() - 1)->y + sizePipe * Utility::randf(-10, 10),
		listesPointsCourbures.at(listesPointsCourbures.size() - 1)->z + sizePipe * Utility::randf(-10, 10)
	));
	int id = listesPointsCourbures.size();

	Pipeline_Part_CMR* part = new Pipeline_Part_CMR(
		listesPointsCourbures.at(id - 5),
		listesPointsCourbures.at(id - 4),
		listesPointsCourbures.at(id - 3),
		listesPointsCourbures.at(id - 2),
		listesPointsCourbures.at(id - 1),
		v, sizePipe, N, mats, nbPartCreated
	);

	std::vector<Vector> vv = part->getV();
	v = vv.at(vv.size() - 1);
	nbPartCreated++;
	parts.push_back(part);
	if (nbPartCreated > 5) {
		Point pmin, pmax;
		Obstacle.bounds(pmin, pmax);

		part->genColision(this, 2, pmin, pmax);
	}
}



void Pipeline::deleteLastPart() {
	for (int i = 0; i < requestDeleteNB; i++) {
		requestDeleteNB--;
		Point* p = listesPointsCourbures.at(0);
		Pipeline_Part_CMR* f = parts.at(0);

		parts.erase(parts.begin());
		listesPointsCourbures.erase(listesPointsCourbures.begin());

		delete p;
		delete f;
		posR += Pipeline_Part_CMR::NB_POINTS;
	}
}

void Pipeline::requestDelete() {
	requestDeleteNB++;
}




float Pipeline::getSizePipe() {
	return sizePipe;
}




Point Pipeline::getPosition(float pos) {
	int m = std::floorf(pos - posR), n = std::ceilf(pos - posR + 0.01);
	float intPart;
	float floatPart = std::modf(pos, &intPart);

	int mm = m / Pipeline_Part_CMR::NB_POINTS;
	int nn = n / Pipeline_Part_CMR::NB_POINTS;

	int mmm = m - mm * Pipeline_Part_CMR::NB_POINTS;
	int nnn = n - nn * Pipeline_Part_CMR::NB_POINTS;

	return (1 - floatPart) * parts.at(mm)->getPoints().at(mmm) + (floatPart)*parts.at(nn)->getPoints().at(nnn);
}

Vector Pipeline::getNormal(float pos) {
	int m = std::floorf(pos - posR), n = std::ceilf(pos - posR + 0.01);
	float intPart;
	float floatPart = std::modf(pos, &intPart);

	int mm = m / Pipeline_Part_CMR::NB_POINTS;
	int nn = n / Pipeline_Part_CMR::NB_POINTS;

	int mmm = m - mm * Pipeline_Part_CMR::NB_POINTS;
	int nnn = n - nn * Pipeline_Part_CMR::NB_POINTS;

	return (1 - floatPart) * parts.at(mm)->getV().at(mmm) + (floatPart)*parts.at(nn)->getV().at(nnn);
}

std::vector<Pipeline_Part_CMR*>& Pipeline::getPart() {
	return parts;
}

Vector Pipeline::getAxe(float pos) {
	return normalize(Vector(
		getPosition(pos - 2) - getPosition(pos + 2)
	));
}

Mesh& Pipeline::getObstacleMesh() { return Obstacle; }

std::vector<TriangleGroup>& Pipeline::getTriangleGroupeObstacle() {
	return group;
}
