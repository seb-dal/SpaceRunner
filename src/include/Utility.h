#pragma once

#include "window.h"

#include "mesh.h"
#include "wavefront.h"  // pour charger un objet au format .obj
#include "orbiter.h"

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include <stdio.h>
#include <vector>
#include "src/include/Pipe.h"

/**
 * Create a Vector from the difference of 2 points
 */
Vector getVector(const Point& from, const Point& to) {
	return Vector(to.x - from.x, to.y - from.y, to.z - from.z);
}

/**
 * return the angle between the Vectors v1 and v2
 */
float getAngleBetweenVectors(const Vector& v1, const Vector& v2) {
	return acos((dot(v1, v2)) / (length(v1) * length(v2)));
}

/**
 * return the rotation XYZ as a Vector of the 2 points
 */
Vector GetAnglesBetween2Points(const Point& from, const Point& to) {
	Vector vec = getVector(from, to);
	return Vector(
		getAngleBetweenVectors(vec, Vector(1, 0, 0)),
		getAngleBetweenVectors(vec, Vector(0, 1, 0)),
		getAngleBetweenVectors(vec, Vector(0, 0, 1))
	);
}

Point interPoint(Point& from, Point& to, float r) {
	return Point(from + r * (to - from));
}

/**
 *
 */
std::vector<Point> subdivisionPoint(std::vector<Point>& pointInit, int iteration, double r) {
	std::vector<Point> result(pointInit);

	if (0.5 <= r && r < 1.0) {
		for (int it = 0; it < iteration; it++) {
			std::vector<Point> temp(result);
			result.clear();
			size_t size = temp.size() - 1;
			//std::cout << size << std::endl;
			//result.push_back(temp[0]);
			if (r > 0.5) {
				for (size_t i = 1; i < size; i++) {
					result.push_back(interPoint(temp[i - 1], temp[i], r));

					result.push_back(interPoint(temp[i], temp[i + 1], 1.0 - r));
				}
			}
			else {
				for (size_t i = 0; i < size; i++) {
					result.push_back(interPoint(temp[i], temp[i + 1], r));
				}
			}
			//result.push_back(temp[size]);
			//std::cout << result.size() << std::endl;
		}
	}
	else {
	}
	return result;
}


/**
 *
 */
void drawLine(Mesh& line, std::vector<Point>& listPoint) {
	line.vertex(listPoint[0]);
	for (size_t i = 1; i < listPoint.size() - 1; i++) {
		line.vertex(listPoint[i]);
		line.vertex(listPoint[i]);
	}
	line.vertex(listPoint[listPoint.size() - 1]);
}

/**
 *
 */
void drawLineWithVec(Mesh& line, std::vector<Point>& listPoint) {
	std::vector<Vector> v;

	Vector vec(1, 0, 0);

	vec = vec * getVector(listPoint[1], listPoint[0]);

	float sizeTipe = 8;
	v.push_back((vec)*sizeTipe);
	for (size_t i = 1; i < listPoint.size() - 1; i++) {
		Transform m = Rotation(getVector(listPoint[i], listPoint[i - 1]), getVector(listPoint[i + 1], listPoint[i]));
		vec = m(vec);
		v.push_back((vec)*sizeTipe);
	}
	v.push_back((vec + (v[v.size() - 1] - v[v.size() - 2])) * sizeTipe);

	line.color(Red()).vertex(listPoint[0]);
	line.color(Red()).vertex(listPoint[0] + v[0]);

	line.color(White()).vertex(listPoint[0]);
	for (size_t i = 1; i < listPoint.size(); i++) {
		line.color(White()).vertex(listPoint[i]);

		line.color(Red()).vertex(listPoint[i]);
		line.color(Red()).vertex(listPoint[i] + v[i]);
		//std::cout << listPoint[i] << " -> " << listPoint[i] + v[i] << "(" << v[i] << ")" << std::endl;

		line.color(White()).vertex(listPoint[i]);
	}
	line.color(White()).vertex(listPoint[listPoint.size() - 1]);
}


void buildPipe(Mesh& quad, std::vector<Point>& listPoint) {
	std::vector<Vector> v;

	Vector vec(1, 0, 0);
	vec = vec * getVector(listPoint[1], listPoint[0]);

	float sizeTipe = 8;
	v.push_back((vec)*sizeTipe);
	for (size_t i = 1; i < listPoint.size() - 1; i++) {
		Transform m = Rotation(getVector(listPoint[i], listPoint[i - 1]), getVector(listPoint[i + 1], listPoint[i]));
		vec = m(vec);
		v.push_back((vec)*sizeTipe);
	}
	v.push_back((vec + (v[v.size() - 1] - v[v.size() - 2])) * sizeTipe);


	int mat = 0;
	Material wg = Material(Color(0.8, 0.8, 0.8));
	int wg_index = quad.materials().insert(wg, "WhiteGray");
	quad.material(wg_index);

	Pipe pipe = Pipe(16);
	for (size_t i = 0; i < listPoint.size() - 1; i++) {
		pipe.addCircule(listPoint[i], 4, getVector(listPoint[i], listPoint[i + 1]), v[i]);
	}
	pipe.addCircule(listPoint[listPoint.size() - 1], 4, getVector(listPoint[listPoint.size() - 2], listPoint[listPoint.size() - 1]), v[listPoint.size() - 1]);

	pipe.drawPipe(quad, wg_index);

}