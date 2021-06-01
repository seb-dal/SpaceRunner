#pragma once

#include <src/gKit/vec.h>
#include <src/gKit/mesh.h>
#include <runner/include/PipeBuilder.h>
#include <runner/include/box.hpp>
#include <runner/include/ObstacleObj.h>
#include <runner/include/BonusObj.h>

class Pipeline;

class Pipeline_Part_CMR {
	const float sizePipe;
	const float NumPart;
	const Point* prev, * start, * end, * after;
	Mesh* fragment;
	unsigned int N;

	std::vector<ObstacleObj*> list_Obstacle;
	std::vector<BonusObj*> list_Bonus;


	std::vector<Vector> v;
	std::vector<Point> listPoints;
public:
	static const float NB_POINTS;

	/**
	 * Create a new part of the pipe.
	 *
	 * \param prevPrev preview preview point
	 * \param prev preview
	 * \param start start coubre point
	 * \param end  end courbe point
	 * \param after point after
	 * \param v last normal of the pipe
	 * \param sizePipe radius of the pipe
	 * \param N number of points per circule
	 * \param mats list color material
	 */
	Pipeline_Part_CMR(
		const Point* prevPrev,
		const Point* prev, const Point* start, const Point* end, const Point* after,
		const Vector& v, const float sizePipe, const unsigned int N, std::vector<Color>& mats,
		const float NumPart
	);

	/**
	 * delete part.
	 */
	~Pipeline_Part_CMR();

	/**
	 * get fragment.
	 *
	 * \return
	 */
	Mesh* get();

	std::vector<ObstacleObj*>& getObstacles();

	std::vector<BonusObj*>& getBonus();
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
	void genColision(MeshLoader& loader, Pipeline* pipe, unsigned int nbColision, unsigned int nbBonus);
};

