#include "include/App_Runner.h"

#include <runner/src/include/Utility.h>
#include <runner/src/include/FPS.h>


App_Runner::App_Runner(const int width, const int height) :App(width, height), camera(Camera(window_width(), window_height(), 45, 0.1, 200)) {
	init_cylinder();
	srand(time(NULL));
}

int App_Runner::init() {

	// etape 1 : charger un objet
	//objet= read_mesh("data/flat_bbox.obj");
	Mesh line(GL_TRIANGLES); // MODE ligne (2 points)



	std::vector<Point> listPoint;
	listPoint.push_back(Point(0, 0, 0));
	listPoint.push_back(Point(100, 100, 100));
	for (int i = 0; i < 50; i++) {
		listPoint.push_back(Point(
			listPoint.at(listPoint.size() - 1).x + sizePipe * 20.f,
			listPoint.at(listPoint.size() - 1).y + sizePipe * Utility::randf(-20, 20),
			listPoint.at(listPoint.size() - 1).z + sizePipe * Utility::randf(-20, 20)
		));
	}
	//drawLine(line, listPoint);
	std::cout << "" << std::endl;
	//std::cout<< <<std::endl;
	//RoadBot rb(0.01f, 0.8f, Point(0, 0, 0), Vector(1, 0, 0));


	subPoint = Utility::subdivisionPoint(listPoint, 8);
	/*for (int i = 1; i < subPoint.size() - 1; i++) {
		std::cout << GetAnglesBetween2Points(subPoint[i - 1], subPoint[i]) << std::endl;
	}*/

	//Utility::drawLineWithVec(line, subPoint, v);
	Utility::buildPipe(line, subPoint, v, sizePipe);

	//============================================================================
	objet = line;
	// etape 2 : creer une camera pour observer l'objet
	// construit l'englobant de l'objet, les extremites de sa boite englobante
	Point pmin, pmax;
	objet.bounds(pmin, pmax);

	// regle le point de vue de la camera pour observer l'objet
	cam2.lookat(pmin, pmax);

	cam2.translation(0.4, -0.4);

	// etat openGL par defaut
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre

	// etape 3 : configuration du pipeline.
/* pour obtenir une image correcte lorsque l'on dessine plusieurs triangles, il faut choisir lequel conserver pour chaque pixel...
	on conserve le plus proche de la camera, celui que l'on voit normalement. ce test revient a considerer que les objets sont opaques.
 */
	glClearDepth(1.f);                          // profondeur par defaut
	glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
	glEnable(GL_DEPTH_TEST);                    // activer le ztest

	return 0;   // ras, pas d'erreur
}






int App_Runner::quit() {
	// etape 3 : detruire la description du triangle
	objet.release();
	return 0;   // ras, pas d'erreur
}


static float totalTime;
static size_t i = 10;
static Point a, b;
/**
	@Param time temps depuis le lancement de l'app (en ms)
	@Param delta temps depuis l'image precedante (en ms)
*/
int App_Runner::update(const float time, const float delta) {
	totalTime = time;
	float fps = FPS::getFPS(delta);
	std::cout << "time:" << time << "  delta:" << delta << "  FPS:" << fps << "\n";



	if (key_state(SDLK_LEFT))
		rotationCircule = std::fmod(rotationCircule - vitesseRot * (fps / 60) + 360, 360);
	if (key_state(SDLK_RIGHT))
		rotationCircule = std::fmod(rotationCircule + vitesseRot * (fps / 60) + 360, 360);

	if (key_state(SDLK_UP))
		if (i < subPoint.size() - 10)
			i++;

	if (key_state(SDLK_DOWN))
		if (i > 10)
			i--;


	Vector axis = Utility::getVector(subPoint[i - 2], subPoint[i + 2]);

	a = Utility::rotAround(subPoint[i], sizePipe + 2, axis, v[i], rotationCircule);
	b = Utility::rotAround(subPoint[i + 2], sizePipe + 2, axis, v[i + 2], rotationCircule);
	//camera.lookat(subPoint[i], subPoint[i + 10]);

	camera.lookAt(
		Utility::rotAround(subPoint[i - 10], sizePipe + 4, axis, v[i - 10], rotationCircule),
		Utility::rotAround(subPoint[i + 3], sizePipe + 2, axis, v[i + 3], rotationCircule),
		Rotation(axis, rotationCircule)(v[i + 1])
	);


	std::cout << "rot" << rotationCircule << " i:" << i << "\n";

	std::cout << "\n";
	return 0;
}







int App_Runner::render() {
	// etape 2 : dessiner l'objet avec opengl

	// on commence par effacer la fenetre avant de dessiner quelquechose
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// on efface aussi le zbuffer

	// on dessine le triangle du point de vue de la camera
	//draw(objet, camera);

	//return 1;   // on continue, renvoyer 0 pour sortir de l'application

	//long int gpu_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
	// on peut aussi controler la camera avec les mouvements de la souris

		// recupere les mouvements de la souris, utilise directement SDL2
	int mx, my;
	unsigned int mb = SDL_GetRelativeMouseState(&mx, &my);

	// deplace la camera
	if (mb & SDL_BUTTON(1))              // le bouton gauche est enfonce
		// tourne autour de l'objet
		cam2.rotation(mx, my);

	else if (mb & SDL_BUTTON(3))         // le bouton droit est enfonce
		// approche / eloigne l'objet
		cam2.move(mx);

	else if (mb & SDL_BUTTON(2))         // le bouton du milieu est enfonce
		// deplace le point de rotation
		cam2.translation((float)mx / (float)window_width(), (float)my / (float)window_height());


	draw_cylinder(a, b, 0.2);

	draw(objet, Transform(), camera.get_Camera(), camera.get_Projection());
	draw(objet, Scale(0.25), cam2);
	return 1;
}





void App_Runner::init_cylinder()
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

void App_Runner::draw_cylinder(const Transform& T)
{
	draw(m_cylinder, T, camera.get_Camera(), camera.get_Projection());

	Transform Tch = T * Translation(0, 1, 0);
	draw(m_cylinder, Tch, camera.get_Camera(), camera.get_Projection());

	//Transform Tcb = T  * Translation( 0, -1, 0);
	Transform Tcb = T * Translation(0, 0, 0) * Rotation(Vector(1, 0, 0), 180);
	draw(m_cylinder, Tcb, camera.get_Camera(), camera.get_Projection());
}


void App_Runner::draw_cylinder(const Point& a, const Point& b, float r = 1.f)
{
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
	//cout << T[0] << endl;
	//cout << T[1] << endl;
	//cout << T[2] << endl;
	//cout << T[3] << endl;

	draw_cylinder(Translation(Vector(a)) * T * Scale(r, lab, r));
}
