#include "runner/include/Pipeline.h"

Pipeline::Pipeline(MeshLoader& loader, int sizePipe, unsigned int N) :sizePipe(sizePipe), N(N) {

	float L = 8.0f;
	float X = (float)N / L;
	float i;
	for (i = 0; i < X; i++) {
		float C = (i / X) * M_PI * 2.f;
		/*Material col = Material(
		Color(
		std::cos(C),
		std::cos(C + (2.0f / 3.0f) * M_PI),
		std::cos(C + (4.0f / 3.0f) * M_PI)
		)
		);*/
		listMaterialColor.push_back(
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

	Vector vec(1, 1, -1);

	if (length(normalize(vec) + normalize(Utility::getVector(*listesPointsCourbures[1], *listesPointsCourbures[0]))) == 0) {
		Vector vec = Vector(0, 0, 1);
		lastNormal = normalize(cross(vec, Utility::getVector(*listesPointsCourbures[1], *listesPointsCourbures[0])));
	}
	else {
		lastNormal = normalize(cross(vec, Utility::getVector(*listesPointsCourbures[1], *listesPointsCourbures[0])));
	}

	//PreCreate 12 pipe fragments on Creation
	int ii;
	for (ii = 0; ii < 12; ii++) {
		addNewPart(loader);
	}
}



Pipeline::~Pipeline() {
	int i;
	for (i = 0; i < parts.size(); i++) {
		delete parts.at(i);
	}

	for (i = 0; i < listesPointsCourbures.size(); i++) {
		delete listesPointsCourbures.at(i);
	}

	listMaterialColor.clear();
}




void Pipeline::addNewPart(MeshLoader& loader) {
	size_t id = listesPointsCourbures.size() - 1;

	listesPointsCourbures.push_back(new Point(
		listesPointsCourbures.at(id)->x + sizePipe * 20.f,
		listesPointsCourbures.at(id)->y + sizePipe * Utility::randf(-10, 10),
		listesPointsCourbures.at(id)->z + sizePipe * Utility::randf(-10, 10)
	));

	Pipeline_Part_CMR* part = new Pipeline_Part_CMR(
		listesPointsCourbures.at(id - 3),
		listesPointsCourbures.at(id - 2),
		listesPointsCourbures.at(id - 1),
		listesPointsCourbures.at(id),
		listesPointsCourbures.at(id + 1),
		lastNormal, sizePipe, N, listMaterialColor, nbPartCreated
	);

	std::vector<Vector> vv = part->getV();
	lastNormal = vv.at(vv.size() - 1);
	nbPartCreated++;
	parts.push_back(part);

	if (nbPartCreated > 6) {
		part->genColision(loader, this, 2, 1);
	}
}



void Pipeline::deleteLastPart() {
	int i;
	for (i = 0; i < requestDeleteNB; i++) {
		requestDeleteNB--;
		Point* p = listesPointsCourbures.at(0);
		Pipeline_Part_CMR* f = parts.at(0);

		parts.erase(parts.begin());
		listesPointsCourbures.erase(listesPointsCourbures.begin());

		delete p;
		delete f;

		//play.decreasePos(Pipeline_Part_CMR::NB_POINTS);
		posR += Pipeline_Part_CMR::NB_POINTS;
	}
}




void Pipeline::requestDelete() { requestDeleteNB++; }




float Pipeline::getSizePipe() { return sizePipe; }




Point Pipeline::getPosition(float pos) {
	float pmpr = pos - posR;
	int m = std::floorf(pmpr), n = std::ceilf(pmpr + 0.01);
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




std::vector<Pipeline_Part_CMR*>& Pipeline::getPart() { return parts; }




Vector Pipeline::getAxe(float pos) {
	return normalize(Vector(
		getPosition(pos - 2) - getPosition(pos + 2)
	));
}

