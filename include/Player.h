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

	Mesh* object;
	std::vector<TriangleGroup>* groups;

	Transform objModel;
	Box colision;


	Camera camera;

	int HIT_Animation = 0;
	int HIT_When = 0;
public:
	static const float vitesseRot;
	static const float vitMax;
	static const int ms_Hit_Anim;

	Player(MeshLoader& loader, const float sizePipe, const float zoom);

	~Player();

	void action(float TotalTime, float fps, Pipeline* pipe);

	float getPos();

	//void decreasePos(const float dec);

	Camera& getCamera();

	Mesh& getObject();
	std::vector<TriangleGroup>& getGroupeTriangle();

	Transform& getObjModel();
	Box& getCollision();

	/**
	 * Decrease the speed of the player to 0.
	 *
	 */
	void stopSpeed();

	void hitObstacle(float when);
	int getHealth();
	int getHIT_Animation();

	void collectBonus(float* scoreValue);
	int getCollectedBonus();


	/**
	 * reset all value in case of game over.
	 */
	void reset();
};

