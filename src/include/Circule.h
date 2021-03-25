#pragma once
#include <vector>
#include "mesh.h"

class Circule {
public:
	Point** listPoints;

	Circule(unsigned int N, const Point& center, float size, const Vector& axis, const Vector& v) {
		listPoints = new Point * [N];
		for (int i = 0; i < N; i++) {
			float angle = i * ((360.0) / N);
			Transform m = Rotation(axis, angle);
			listPoints[i] = new Point(center + m(v));
		}
	}

	~Circule() {
		delete[] listPoints;
	}
};
