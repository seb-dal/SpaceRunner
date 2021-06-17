#include "runner/include/Utility.h"




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




Vector Utility::getVector(const Point& from, const Point& to) {
	return Vector(to.x - from.x, to.y - from.y, to.z - from.z);
}




float Utility::getAngleBetweenVectors(const Vector& v1, const Vector& v2) {
	return acos((dot(v1, v2)) / (length(v1) * length(v2)));
}





Vector Utility::GetAnglesBetween2Points(const Point& from, const Point& to) {
	Vector vec = getVector(from, to);
	return Vector(
		getAngleBetweenVectors(vec, Vector(1, 0, 0)),
		getAngleBetweenVectors(vec, Vector(0, 1, 0)),
		getAngleBetweenVectors(vec, Vector(0, 0, 1))
	);
}




std::vector<Point> Utility::subdivisionPoint(std::vector<Point>& pointInit, int iteration) {
	std::vector<Point> result(pointInit);
	int it;
	size_t i;
	for (it = 0; it < iteration; it++) {
		std::vector<Point> temp(result);
		result.clear();
		size_t size = temp.size() - 1;
		//std::cout << size << std::endl;
		//result.push_back(temp[0]);
		for (i = 1; i < size; i++) {
			result.push_back(interPoint(temp[i - 1], temp[i], 0.75));
			result.push_back(interPoint(temp[i], temp[i + 1], 0.25));
		}

	}

	return result;
}





void Utility::drawLine(Mesh& line, std::vector<Point>& listPoint) {
	line.vertex(listPoint[0]);
	size_t i, max = listPoint.size() - 1;
	for (i = 1; i < max; i++) {
		line.vertex(listPoint[i]);
		line.vertex(listPoint[i]);
	}
	line.vertex(listPoint[max]);
}




void Utility::buildPerpendicularVect(std::vector<Point>& listPoint, std::vector<Vector>& v, const Vector& init) {

	v = std::vector<Vector>(listPoint.size());
	Vector vec(init);
	//vec = normalize(vec * getVector(listPoint[1], listPoint[0]));

	v[0] = ((vec)); // list des transformations
	size_t i;
	for (i = 1; i < listPoint.size() - 1; i++) {

		vec = normalize(
			Rotation(
				getVector(listPoint[i], listPoint[i - 1]),
				getVector(listPoint[i + 1], listPoint[i])
			)(vec)
		);

		v[i] = vec;
	}
	v[v.size() - 1] = normalize(vec + v[v.size() - 2]);
}






void Utility::drawLineWithVec(Mesh& line, const std::vector<Point>& listPoint, const std::vector<Vector>& v) {
	line.color(Red()).vertex(listPoint[0]);
	line.color(Red()).vertex(listPoint[0] + v[0]);

	line.color(White()).vertex(listPoint[0]);
	size_t i;
	for (i = 1; i < listPoint.size(); i++) {
		line.color(White()).vertex(listPoint[i]);

		line.color(Red()).vertex(listPoint[i]);
		line.color(Red()).vertex(listPoint[i] + v[i]);
		//std::cout << listPoint[i] << " -> " << listPoint[i] + v[i] << "(" << v[i] << ")" << std::endl;

		line.color(White()).vertex(listPoint[i]);
	}
	line.color(White()).vertex(listPoint[listPoint.size() - 1]);
}






void Utility::buildPipe(Mesh& quad, std::vector<Point>& listPoint, std::vector<Vector>& v, float sizePipe) {
	buildPerpendicularVect(listPoint, v, Vector(1, 0, 0));

	std::vector<Color> mats; // listes des materiaux
	int N = 16;
	float L = 8.0f;
	float X = N / L;
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
		mats.push_back(
			Color(
				0.5 * std::cos(C / 2),
				0,//std::cos(C),
				std::cos(C / 2)
			)
		);
	}

	PipeBuilder pipe = PipeBuilder(N);
	size_t j, size;
	for (j = 0; j < listPoint.size() - 1; j++) {
		pipe.addCircule(
			listPoint[j],
			sizePipe,
			getVector(
				listPoint[j],
				listPoint[j + 1]
			),
			v[j]
		);
	}


	size = listPoint.size() - 1;
	pipe.addCircule(
		listPoint[size],
		sizePipe,
		getVector(
			listPoint[size - 1],
			listPoint[size]
		),
		v[size]
	);


	pipe.drawPipe(quad, mats);
}






float Utility::randf() {
	return 1.f - ((float)rand() / ((float)RAND_MAX / 2.f));
}



float Utility::randomf() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
}



float Utility::randf(const float LO, const float HI) {
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}



Point Utility::rotAround(const Point& center, float size, const Vector& axis, const Vector& normal, float angle) {
	return center + Scale(size)(Rotation(normalize(axis), angle)(normalize(normal)));
}



float Utility::GetT(const float t, const float alpha, const Point& p0, const Point& p1) {
	auto d = p1 - p0;
	float a = dot(d, d); // Dot product
	float b = std::pow(a, alpha * .5f);
	return (b + t);
}



float Utility::lerp(float a, float b, float t) {
	return a + t * (b - a);
}



Point Utility::CatMullRom(const Point& p0, const Point& p1, const Point& p2, const Point& p3, float t, float alpha) {
    // https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
	float t0 = 0.0f;
	float t1 = GetT(t0, alpha, p0, p1);
	float t2 = GetT(t1, alpha, p1, p2);
	float t3 = GetT(t2, alpha, p2, p3);

	t = lerp(t1, t2, t);

	float tmt0 = t - t0;
	float tmt1 = t - t1;
	float t2mt = t2 - t;
	float t3mt = t3 - t;
	float t1mt2 = t1 - t0;
	float t2mt1 = t2 - t1;
	float t3mt2 = t3 - t2;
	float t2mt0 = t2 - t0;
	float t3mt1 = t3 - t1;

	Point A1 = (t1 - t) / (t1mt2)*p0 + (tmt0) / (t1mt2)*p1;
	Point A2 = (t2mt) / (t2mt1)*p1 + (tmt1) / (t2mt1)*p2;
	Point A3 = (t3mt) / (t3mt2)*p2 + (t - t2) / (t3mt2)*p3;

	Point B1 = (t2mt) / (t2mt0)*A1 + (tmt0) / (t2mt0)*A2;
	Point B2 = (t3mt) / (t3mt1)*A2 + (tmt1) / (t3mt1)*A3;

	Point C = (t2mt) / (t2mt1)*B1 + (tmt1) / (t2mt1)*B2;

	return C;
}




Transform Utility::modelOnPipe(Pipeline* pipe, const float position, const float heightOnPipe, const float rotation) {
	float posm1 = position - 1, posp1 = position + 1;

	Transform model = (Utility::Lookat(
		Utility::rotAround(
			pipe->getPosition(posm1),
			heightOnPipe,
			pipe->getAxe(posm1),
			pipe->getNormal(posm1),
			rotation
		),
		Utility::rotAround(
			pipe->getPosition(posp1),
			heightOnPipe,
			pipe->getAxe(posp1),
			pipe->getNormal(posp1),
			rotation
		),
		(Rotation(pipe->getAxe(position), rotation))(pipe->getNormal(position))
	));


	return model;
}




Transform Utility::Lookat(const Point& from, const Point& to, const Vector& up) {
	Vector dir = normalize(Vector(from, to));
	Vector right = normalize(cross(dir, normalize(up)));
	Vector newUp = normalize(cross(right, dir));

	Transform m(
		right.x, newUp.x, -dir.x, from.x,
		right.y, newUp.y, -dir.y, from.y,
		right.z, newUp.z, -dir.z, from.z,
		0, 0, 0, 1);

	return m;
}

