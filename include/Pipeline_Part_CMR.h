#pragma once

#include <src/gKit/vec.h>
#include <src/gKit/mesh.h>
#include <runner/include/PipeBuilder.h>
#include <box-intersection-etu/box.hpp>

class Pipeline;

class Pipeline_Part_CMR {
	const float sizePipe;
	const float NumPart;
	const Point* prev, * start, * end, * after;
	Mesh* fragment;
	unsigned int N;

	std::vector<Box*> list_colision;

	std::vector<Vector> v;
	std::vector<Point> listPoints;
public:
	static const float NB_POINTS;
	/**
	 * .
	 * \param prevPrev
	 * \param prev
	 * \param start
	 * \param end
	 * \param after
	 * \param v
	 * \param sizePipe
	 * \param N
	 * \param mats
	 */
	Pipeline_Part_CMR(
		const Point* prevPrev,
		const Point* prev, const Point* start, const Point* end, const Point* after,
		const Vector& v, const float sizePipe, const unsigned int N, std::vector<Color>& mats,
		const float NumPart
	);

	/**
	 * delete.
	 */
	~Pipeline_Part_CMR();

	/**
	 * get fragment.
	 *
	 * \return
	 */
	Mesh* get();

	std::vector<Box*>& getColision();

	/**
	 * get Points.
	 */
	std::vector<Point>& getPoints();

	/**
	 * get list normal pipe.
	 */
	std::vector<Vector>& getV();

	/**
	 * Generate the colision box.
	 *
	 * \param pipe pointer of th pipe
	 * \param nbColision number of colision box that will be create
	 * \param pmin
	 * \param pmax
	 */
	void genColision(Pipeline* pipe, unsigned int nbColision, Point pmin, Point pmax);
};

