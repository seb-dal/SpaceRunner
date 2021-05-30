#pragma once
#include <src/gKit/mat.h>
#include <src/gKit/mesh.h>
#include <runner/include/Camera.h>
#include <runner/include/Pipeline.h>
#include <box-intersection-etu/box.hpp>
#include <src/gKit/wavefront.h>
#include <src/gKit/window.h>

class Player {
	float rotationCircule = 0;
	const float vitesseRot = 1;
	const float vitesse = 1;
	float pos = 10;

	Mesh object;
	std::vector<TriangleGroup> groups;

	Transform objModel;
	Box colision;


	Camera camera;


public:
	Player(const float sizePipe, const float zoom);

	~Player();

	void action(float fps, Pipeline* pipe);

	float getPos();

	Camera& getCamera();

	Mesh& getObject();

	Transform& getObjModel();

	std::vector<TriangleGroup>& getGroupeTriangle();

	Box getCollision();
};

