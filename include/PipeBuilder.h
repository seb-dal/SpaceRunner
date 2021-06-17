#pragma once

#include <vector>
#include "mesh.h"
#include <runner/include/PointMesh.h>
#include <runner/include/Circule.h>



class PipeBuilder {
	unsigned int N;
	std::vector<Circule*> listSegmentCircule;

public:
	PipeBuilder(unsigned int N);

	~PipeBuilder();

	/**
	 * NO LONGER USED.
	 */
	void removeFirst();


	/**
	 * Draw the pipe in a mesh.
	 *
	 * \param obj Mesh
	 * \param v list of color
	 */
	void drawPipe(Mesh& obj, std::vector<Color>& v);

	/**
	 * resize the vector list with a size.
	 *
	 * \param size number of circule
	 */
	void allocCircule(const size_t size);

	/**
	 * Add a new circule to the the list of circule with push_back.
	 *
	 * \param center center of the circule
	 * \param size size of the circule
	 * \param axis axis around which the circule rotate
	 * \param v normal of the pipe
	 */
	void addCircule(const Point& center, float size, const Vector& axis, const Vector& v);

	/**
	 * Add a new circule to the list of circule with a position in the list.
	 *
	 * \param pos position to add the circule in the list
	 * \param center center of the circule
	 * \param size size of the circule
	 * \param axis axis around which the circule rotate
	 * \param v normal of the pipe
	 */
	void addCircule(const unsigned int pos, const Point& center, float size, const Vector& axis, const Vector& v);
};
