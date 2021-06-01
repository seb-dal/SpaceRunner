#pragma once

#include <src/gKit/mesh.h>
#include <app.h>

class Viewer : public App {
public:
	Viewer(const int width, const int height);

	int init();

	int quit();

	void draw_cube(const Transform& T, Transform& camera, Transform& projection);

	void draw_cylinder(const Transform& T, Transform& camera, Transform& projection);
	void draw_cylinder(Transform& camera, Transform& projection, const Point& a, const Point& b, float r);

protected:
	Mesh m_cube;
	void init_cube();

	Mesh m_cylinder;
	Mesh m_cylinder_cover;
	void init_cylinder();


};
