#pragma once

#include <vector>
#include <src/gKit/vec.h>
#include <runner/include/Pipeline_Part_CMR.h>

class Pipeline_Part_CMR;
class MeshLoader;

class Pipeline {
	const float sizePipe;
	const unsigned int N;

	float posR = 0;
	float nbPartCreated = 0;
	std::vector<Point*> listesPointsCourbures;
	std::vector<Pipeline_Part_CMR*> parts;

	int requestDeleteNB = 0;


	std::vector<Color> listMaterialColor;

	Vector lastNormal;
public:
	/**
	 * .
	 *
	 * \param sizePipe
	 * \param N
	 */
	Pipeline(MeshLoader& loader, int sizePipe, unsigned int N);

	~Pipeline();

	/**
	 * Ajoute une nouvelle parti.
	 *
	 */
	void addNewPart(MeshLoader& loader);

	/**
	 * Supprimer la dernier partie / point.
	 *
	 */
	void deleteLastPart();

	/**
	 * Request to delete the last part by the main thread.
	 *
	 */
	void requestDelete();


	/**
	 * Get the radius of the pipe.
	 *
	 * \return
	 */
	float getSizePipe();


	/**
	 * Get the position of the center of the pipe.
	 *
	 * \param pos position on the pipe
	 * \return center of the pipe at the given position
	 */
	Point getPosition(float pos);

	/**
	 * Get normal of the pipe at the given position.
	 *
	 * \param pos position on the pipe
	 * \return Vector normal
	 */
	Vector getNormal(float pos);

	/**
	 * Get all part of the pipe.
	 *
	 * \return list of part of the pipe
	 */
	std::vector<Pipeline_Part_CMR*>& getPart();

	/**
	 * Get axis of the pipe at the given position.
	 *
	 * \param pos position on the pipe
	 * \return vector axis
	 */
	Vector getAxe(float pos);

};

