#ifndef MIF27_BOX_HPP
#define MIF27_BOX_HPP

#include "vec.h"
#include "mat.h"

class Box {
public:
	Box();
	Box(const Point& pmin, const Point& pmax);

	/**
	 * Return true if the the two bax collide.
	 *
	 * \param rhs another box
	 * \return ModelMesh or not
	 */
	bool collides(const Box& rhs);

	Point pmin, pmax;
	Transform T;
};

#endif