#pragma once
#include <src/gKit/mat.h>
#include <src/gKit/mesh.h>
#include <runner/include/Camera.h>
#include <runner/include/Pipeline.h>
#include <box-intersection-etu/box.hpp>
#include <src/gKit/wavefront.h>
#include <src/gKit/window.h>


class Player {
	int health = 3;
	int bonusCollect = 0;

	float rotationCircule = 0;
	float vitesse = 0;
	float pos = 10;

	Mesh object;
	std::vector<TriangleGroup> groups;

	Transform objModel;
	Box colision;


	Camera camera;


public:
	static const float vitesseRot;
	static const float vitMax;


	Player(MeshLoader& loader, const float sizePipe, const float zoom);

	~Player();

	void action(float fps, Pipeline* pipe);

	float getPos();

	//void decreasePos(const float dec);

	Camera& getCamera();

	Mesh& getObject();

	Transform& getObjModel();

	std::vector<TriangleGroup>& getGroupeTriangle();

	Box getCollision();

	/**
	 * Decrease the speed of the player to 0.
	 *
	 */
	void stopSpeed();

	void hitObstacle();
	int getHealth();

	void collectBonus(float* scoreValue);

	int getCollectedBonus();

	/**
	 * reset all value in case of game over.
	 */
	void reset();
};

