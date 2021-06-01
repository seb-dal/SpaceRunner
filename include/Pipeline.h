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



	std::vector<Color> mats;
	Vector v;
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


	float getSizePipe();

	Point getPosition(float pos);

	Vector getNormal(float pos);

	std::vector<Pipeline_Part_CMR*>& getPart();

	Vector getAxe(float pos);

};

