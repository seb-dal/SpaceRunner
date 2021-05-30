#include "runner/include/Circule.h"

Circule::Circule(unsigned int N, const Point& center, const float size, const Vector& axis, const Vector& v) {
	this->N = N;
	listPoints = new Point * [N];
	for (unsigned int i = 0; i < N; i++) {
		listPoints[i] = new Point(
			center + Scale(size)(Rotation(normalize(axis), i * ((360.0) / N)))(normalize(v))
		);
	}
}

Circule::~Circule() {
	delete[] listPoints;
}

Point& Circule::get(unsigned int i) {
	return *listPoints[i % N];
}
