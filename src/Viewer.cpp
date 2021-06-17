#include "runner/include/Viewer.h"
#include <src/gKit/draw.h>

Viewer::Viewer(const int width, const int height) :App(width, height) {

}



int Viewer::init() {
	//init_cube();
	//init_cylinder();
	return 0;
}



int Viewer::quit() {
	//m_cube.release();
	//m_cylinder.release();
	//m_cylinder_cover.release();

	return 0;
}




void Viewer::draw_cube(const Transform& T, Transform& camera, Transform& projection) {
	draw(m_cube, T, camera, projection);
}



void Viewer::init_cube()
{
	//                          0           1           2       3           4           5       6           7
	static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
	static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
	static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
	int i;

	m_cube = Mesh(GL_TRIANGLE_STRIP);
	m_cube.color(Color(1, 1, 1));

	for (i = 0; i < 6; i++)
	{
		m_cube.normal(n[i][0], n[i][1], n[i][2]);

		m_cube.texcoord(0, 0);
		m_cube.vertex(pt[f[i][0]][0], pt[f[i][0]][1], pt[f[i][0]][2]);

		m_cube.texcoord(1, 0);
		m_cube.vertex(pt[f[i][1]][0], pt[f[i][1]][1], pt[f[i][1]][2]);

		m_cube.texcoord(0, 1);
		m_cube.vertex(pt[f[i][3]][0], pt[f[i][3]][1], pt[f[i][3]][2]);

		m_cube.texcoord(1, 1);
		m_cube.vertex(pt[f[i][2]][0], pt[f[i][2]][1], pt[f[i][2]][2]);

		m_cube.restart_strip();
	}
}



void Viewer::init_cylinder()
{
	int i;
	const int div = 25;
	float alpha;
	float step = 2.0 * M_PI / (div);

	m_cylinder = Mesh(GL_TRIANGLE_STRIP);

	for (i = 0; i <= div; ++i)
	{
		alpha = i * step;
		m_cylinder.normal(Vector(cos(alpha), 0, sin(alpha)));
		m_cylinder.texcoord(float(i) / div, 0.f);
		m_cylinder.vertex(Point(cos(alpha), 0, sin(alpha)));

		m_cylinder.normal(Vector(cos(alpha), 0, sin(alpha)));
		m_cylinder.texcoord(float(i) / div, 1.f);
		m_cylinder.vertex(Point(cos(alpha), 1, sin(alpha)));
	}

	m_cylinder_cover = Mesh(GL_TRIANGLE_FAN);

	m_cylinder_cover.normal(Vector(0, 1, 0));

	m_cylinder_cover.vertex(Point(0, 0, 0));
	for (i = 0; i <= div; ++i)
	{
		alpha = -i * step;
		m_cylinder_cover.vertex(Point(cos(alpha), 0, sin(alpha)));
	}
}




void Viewer::draw_cylinder(const Transform& T, Transform& camera, Transform& projection)
{
	draw(m_cylinder, T, camera, projection);

	Transform Tch = T * Translation(0, 1, 0);
	draw(m_cylinder, Tch, camera, projection);

	//Transform Tcb = T  * Translation( 0, -1, 0);
	Transform Tcb = T * Translation(0, 0, 0) * Rotation(Vector(1, 0, 0), 180);
	draw(m_cylinder, Tcb, camera, projection);
}




void Viewer::draw_cylinder(Transform& camera, Transform& projection, const Point& a, const Point& b, float r = 1.f) {
	Vector ab = b - a;
	Vector p, y, z;
	Vector abn = normalize(ab);
	float lab = length(ab);
	if (lab < 0.00001f) return;
	if (fabs(ab.x) > 0.25f)
		p = Vector(0, 1, 0);
	else
		p = Vector(1, 0, 0);

	y = cross(abn, p);
	y = normalize(y);
	z = cross(abn, y);
	Transform T(z, abn, y, Vector(0, 0, 0));


	draw_cylinder(Translation(Vector(a)) * T * Scale(r, lab, r), camera, projection);
}


