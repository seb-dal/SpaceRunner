#include "runner/include/App_Runner.h"

#include <runner/include/Utility.h>
#include <runner/include/FPS.h>
#include <runner/include/Drawing.h>


App_Runner::App_Runner(const int width, const int height)
	:App(width, height),
	player(Player(sizePipe, zoom))
{
	init_cylinder();
	srand(time(NULL));
	tuyau = new Pipeline(sizePipe, 32);
}

static float posCreate = 100;
static bool continuCreate = true;
static void createPartIfNeeded(Player& player, Pipeline* tuyau) {
	do {
		if (player.getPos() - posCreate > Pipeline_Part_CMR::NB_POINTS / 2) {
			try {
				posCreate += Pipeline_Part_CMR::NB_POINTS;
				tuyau->addNewPart();
				tuyau->requestDelete();
				std::cout << "New part created" << std::endl;
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
		}
		//else
			//std::cout << "No part created" << std::endl;
		//std::cout << player.getPos() << "  " << posCreate << std::endl;
	} while (continuCreate);
}



int App_Runner::init() {

	thread_PipeBuilder = std::thread(createPartIfNeeded, std::ref(player), std::ref(tuyau));

	// etape 1 : charger un objet
	//objet= read_mesh("data/flat_bbox.obj");
	//Mesh line(GL_TRIANGLES); // MODE ligne (2 points)

	/*std::vector<Point> listPoint;
	listPoint.push_back(Point(0, 0, 0));
	listPoint.push_back(Point(100, 100, 100));
	for (int i = 0; i < 3; i++) {
		listPoint.push_back(Point(
			listPoint.at(listPoint.size() - 1).x + sizePipe * 20.f,
			listPoint.at(listPoint.size() - 1).y + sizePipe * Utility::randf(-20, 20),
			listPoint.at(listPoint.size() - 1).z + sizePipe * Utility::randf(-20, 20)
		));
	}*/
	//drawLine(line, listPoint);
	//std::cout<< <<std::endl;
	//RoadBot rb(0.01f, 0.8f, Point(0, 0, 0), Vector(1, 0, 0));


	//subPoint = Utility::subdivisionPoint(listPoint, 8);
	/*for (int i = 1; i < subPoint.size() - 1; i++) {
		std::cout << GetAnglesBetween2Points(subPoint[i - 1], subPoint[i]) << std::endl;
	}*/

	//Utility::drawLineWithVec(line, subPoint, v);
	//Utility::buildPipe(line, subPoint, v, sizePipe);

	//============================================================================
	//objet = line;
	// etape 2 : creer une camera pour observer l'objet
	// construit l'englobant de l'objet, les extremites de sa boite englobante
	//Point pmin, pmax;
	//objet.bounds(pmin, pmax);

	// regle le point de vue de la camera pour observer l'objet
	//cam2.lookat(pmin, pmax);

	//cam2.translation(0.4, -0.4);

	// etat openGL par defaut
	//glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
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
	//objet.release();
	//delete tuyau;
	continuCreate = false;
	//thread_PipeBuilder.join();
	tuyau->getObstacleMesh().release();
	player.getObject().release();
	return 0;   // ras, pas d'erreur
}


/**
	@Param time temps depuis le lancement de l'app (en ms)
	@Param delta temps depuis l'image precedante (en ms)
*/
int App_Runner::update(const float time, const float delta) {
	float fps = FPS::getFPS(delta);
	std::cout << "time:" << time << "  delta:" << delta << "  FPS:" << fps << "\n";

	player.action(fps, tuyau);

	tuyau->deleteLastPart();

	std::vector<Box*> collisionPart1 = tuyau->getPart()[0]->getColision();
	std::vector<Box*> collisionPart2 = tuyau->getPart()[1]->getColision();
	Box play = player.getCollision();
	for (Box* b : collisionPart1) {
		if (play.collides(*b)) {
			std::cout << "Colision" << std::endl;
		}
	}
	for (Box* b : collisionPart2) {
		if (play.collides(*b)) {
			std::cout << "Colision" << std::endl;
		}
	}

	return 0;
}






int App_Runner::render() {
	Drawing drawer;

	// etape 2 : dessiner l'objet avec opengl
	// on commence par effacer la fenetre avant de dessiner quelquechose
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// on efface aussi le zbuffer

	//draw(objet, Transform(), camera.get_Camera(), camera.get_Projection());
	for (Pipeline_Part_CMR* p : tuyau->getPart()) {
		drawer.draw(player.getCamera(), *p->get(), Identity());
		std::vector<Box*> listC = p->getColision();

		for (int i = 0; i < listC.size(); i++) {
			drawer.draw(player.getCamera(), tuyau->getObstacleMesh(), listC[i]->T, tuyau->getTriangleGroupeObstacle());
		}
		//draw(*nbPartCreated->get(), Identity(), camera.get_Camera(), camera.get_Projection());
	}

	drawer.draw(player.getCamera(), player.getObject(), player.getObjModel(), player.getGroupeTriangle());


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
	draw(m_cylinder, T, player.getCamera().get_Camera(), player.getCamera().get_Projection());

	Transform Tch = T * Translation(0, 1, 0);
	draw(m_cylinder, Tch, player.getCamera().get_Camera(), player.getCamera().get_Projection());

	//Transform Tcb = T  * Translation( 0, -1, 0);
	Transform Tcb = T * Translation(0, 0, 0) * Rotation(Vector(1, 0, 0), 180);
	draw(m_cylinder, Tcb, player.getCamera().get_Camera(), player.getCamera().get_Projection());
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
