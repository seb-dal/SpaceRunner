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
#include <build/Player.h>
#include <runner/src/include/Camera.h>


class App_Runner : public App {
	const float sizePipe = 8;

	float rotationCircule = 0;
	const float vitesseRot = 1;

	Mesh objet;
	Orbiter cam2;
	Camera camera;

	Player play;

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