#pragma once

#include "window.h"
#include "mesh.h"
#include "wavefront.h"  // pour charger un objet au format .obj
#include "orbiter.h"
#include "draw.h"        // pour dessiner du point de vue d'une camera

#include <cmath>

#include <stdio.h>
#include <vector>
#include <app.h>
#include <thread>
#include <runner/include/Player.h>
#include <runner/include/Camera.h>
#include <runner/include/Pipeline.h>


class App_Runner : public App {
	const float sizePipe = 50;
	const float zoom = 2;

	Pipeline* tuyau;
	std::thread thread_PipeBuilder;

	Player player;

	std::vector<Point> subPoint;
	std::vector<Vector> v;

	Mesh m_cylinder;
	Mesh m_cylinder_cover;
	void init_cylinder();

public:
	App_Runner(const int width, const int height);
	virtual int init();
	virtual int quit();
	virtual int update(const float time, const float delta);
	virtual int render();

	void draw_cylinder(const Transform& T);
	void draw_cylinder(const Point& a, const Point& b, float r);
};