#include "runner/include/Circule.h"

Circule::Circule(unsigned int N, const Point& center, const float size, const Vector& axis, const Vector& v) {
	this->N = N;
	listPoints = new Point * [N];
	unsigned int i;
	for (i = 0; i < N; i++) {
		listPoints[i] = new Point(
			center + Scale(size)(Rotation(normalize(axis), i * ((360.0f) / N)))(normalize(v))
		);
	}
}



Circule::~Circule() {
	unsigned int i;
	for (i = 0; i < N; i++) {
		delete listPoints[i];//delete all points first
	}

	delete[] listPoints;//delete the table pointer
}



//circular get point
Point& Circule::get(unsigned int i) { return *listPoints[i % N]; }
