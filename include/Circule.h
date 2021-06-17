#pragma once

#include <vector>
#include "mesh.h"

/**
 * Circle for the Pipe.
 */
class Circule {
public:
	unsigned int N; // number of Points in a Circule
	Point** listPoints; // List of Points

	Circule(unsigned int N, const Point& center, float size, const Vector& axis, const Vector& v);

	~Circule();

	/**
	 * Get the i eme point.
	 * This get work like a circular array i%N
	 *
	 * \param i number of the points
	 * \return Point of the Circle
	 */
	Point& get(unsigned int i);
};
