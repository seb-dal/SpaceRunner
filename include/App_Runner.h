#pragma once

#include "window.h"
#include "mesh.h"
#include "wavefront.h"  // pour charger un objet au format .obj
#include "orbiter.h"
#include "draw.h"        // pour dessiner du point de vue d'une camera

#include <cmath>

#include <stdio.h>
#include <vector>
#include "runner/include/Viewer.h"
#include <thread>
#include <runner/include/Player.h>
#include <runner/include/Camera.h>
#include <runner/include/Pipeline.h>
#include <src/gKit/text.h>
#include <runner/include/MeshLoader.h>


class App_Runner : public Viewer {
	MeshLoader loader;

	const float sizePipe = 50;
	const float zoom = 2;

	Pipeline* tuyau;
	std::thread thread_PipeBuilder;

	Player player;

	//std::vector<Point> subPoint;
	//std::vector<Vector> v;
	bool gameover = false;

	Text score;
	float scoreValue = 0;

	Text fpsDisplay;
	Text gameoverDiplay;


public:
	App_Runner(const int width, const int height);
	virtual int init();
	virtual int quit();
	virtual int update(const float time, const float delta);
	virtual int render();

	/**
	 * Detect all kind of collsion.
	 * Used in update.
	 */
	void collision(float time, float delta);

};