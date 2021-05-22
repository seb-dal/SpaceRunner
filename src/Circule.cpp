#include "runner/src/include/Circule.h"

Circule::Circule(unsigned int N, const Point& center, float size, const Vector& axis, const Vector& v) {
	this->N = N;
	listPoints = new Point * [N];
	for (unsigned int i = 0; i < N; i++) {
		float angle = i * ((360.0) / N);
		Transform m = Rotation(axis, angle);
		listPoints[i] = new Point(center + size * m(v));
	}
}

Circule::~Circule() {
	delete[] listPoints;
}

Point& Circule::get(unsigned int i) {
	return *listPoints[i % N];
}
