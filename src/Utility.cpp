#include "runner/src/include/Utility.h"

/**
* String value of a color.
*/

std::string Utility::toString_Color(Color& c) {
	std::string res;
	res += "R:";
	res += std::to_string(c.r);
	res += " G:";
	res += std::to_string(c.g);
	res += " B:";
	res += std::to_string(c.b);
	res += " A:";
	res += std::to_string(c.a);

	return res;
}

Vector Utility::perpendicular_Vector_Triangle(const Vector& a, const Vector& b, const Vector& c) {
	return normalize(cross((b - a), (c - a)));
}

float Utility::vertical_angle_triangle(const Vector& a, const Vector& b, const Vector& c) {
	Vector p = perpendicular_Vector_Triangle(a, b, c), v(0.0f, 10.0f, 0.0f);
	float res = std::asin(length2(cross(p, v)) / length2(p) / length2(v));
	if (std::isnan(res)) {
		throw std::invalid_argument("res is equal to nan");
	}
	return res;
}

/**
* Create a Vector from the difference of 2 points
*/

Vector Utility::getVector(const Point& from, const Point& to) {
	return Vector(to.x - from.x, to.y - from.y, to.z - from.z);
}

/**
* return the angle between the Vectors v1 and v2
*/

float Utility::getAngleBetweenVectors(const Vector& v1, const Vector& v2) {
	return acos((dot(v1, v2)) / (length(v1) * length(v2)));
}

/**
* return the rotation XYZ as a Vector of the 2 points
*/

Vector Utility::GetAnglesBetween2Points(const Point& from, const Point& to) {
	Vector vec = getVector(from, to);
	return Vector(
		getAngleBetweenVectors(vec, Vector(1, 0, 0)),
		getAngleBetweenVectors(vec, Vector(0, 1, 0)),
		getAngleBetweenVectors(vec, Vector(0, 0, 1))
	);
}

/**
* Get a list of points that are the result of the smoothing of the list of points in param.
*/
std::vector<Point> Utility::subdivisionPoint(std::vector<Point>& pointInit, int iteration) {
	std::vector<Point> result(pointInit);

	for (int it = 0; it < iteration; it++) {
		std::vector<Point> temp(result);
		result.clear();
		size_t size = temp.size() - 1;
		//std::cout << size << std::endl;
		//result.push_back(temp[0]);
		for (size_t i = 1; i < size; i++) {
			result.push_back(interPoint(temp[i - 1], temp[i], 0.75));
			result.push_back(interPoint(temp[i], temp[i + 1], 0.25));
		}

	}

	return result;
}

/**
* Draw a line with a list of points
*/

void Utility::drawLine(Mesh& line, std::vector<Point>& listPoint) {
	line.vertex(listPoint[0]);
	for (size_t i = 1; i < listPoint.size() - 1; i++) {
		line.vertex(listPoint[i]);
		line.vertex(listPoint[i]);
	}
	line.vertex(listPoint[listPoint.size() - 1]);
}

void Utility::buildPerpendicularVect(std::vector<Point>& listPoint, std::vector<Vector>& v) {
	Vector vec(1, 0, 0);
	vec = vec * getVector(listPoint[1], listPoint[0]);

	float sizeTipe = 10;
	v.push_back((vec)*sizeTipe); // list des transformations
	for (size_t i = 1; i < listPoint.size() - 1; i++) {
		Transform m = Rotation(
			getVector(listPoint[i], listPoint[i - 1]),
			getVector(listPoint[i + 1], listPoint[i])
		);
		vec = m(vec);
		v.push_back((vec)*sizeTipe);
	}
	v.push_back((vec + (v[v.size() - 1] - v[v.size() - 2])) * sizeTipe);
}

/**
* Draw a line with with a Vector parallele to the line
*/

void Utility::drawLineWithVec(Mesh& line, std::vector<Point>& listPoint, std::vector<Vector>& v) {
	buildPerpendicularVect(listPoint, v);

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

/**
* Build and draw a pipe.
*/

void Utility::buildPipe(Mesh& quad, std::vector<Point>& listPoint, std::vector<Vector>& v, float sizePipe) {
	buildPerpendicularVect(listPoint, v);

	std::vector<Color> mats; // listes des materiaux
	int N = 16;
	float L = 8.0f;
	float X = N / L;
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

	Pipe pipe = Pipe(N);
	for (size_t i = 0; i < listPoint.size() - 1; i++) {
		pipe.addCircule(
			listPoint[i],
			sizePipe,
			getVector(
				listPoint[i],
				listPoint[i + 1]
			),
			v[i]
		);
	}
	pipe.addCircule(
		listPoint[listPoint.size() - 1],
		sizePipe,
		getVector(
			listPoint[listPoint.size() - 2],
			listPoint[listPoint.size() - 1]
		),
		v[listPoint.size() - 1]
	);


	pipe.drawPipe(quad, mats);
}


/*
*Random value between -1 and 1
*/

float Utility::randf() {
	return 1.f - ((float)rand() / ((float)RAND_MAX / 2.f));
}

float Utility::randomf() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
}

float Utility::randf(const float LO, const float HI) {
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}
