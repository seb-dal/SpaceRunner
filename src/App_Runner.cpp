#include "runner/include/App_Runner.h"

#include <runner/include/Utility.h>
#include <runner/include/FPS.h>
#include <runner/include/Drawing.h>
#include <runner/include/Pipe_Object.h>


App_Runner::App_Runner(const int width, const int height)
	:Viewer(width, height),
	loader(),
	player(Player(loader, sizePipe, zoom))
{
	srand(time(NULL));
	tuyau = new Pipeline(loader, sizePipe, 32);
}



static float posCreate = 100;
static bool continuCreate = true;

static void createPartIfNeeded(Player& player, Pipeline* tuyau, MeshLoader& loader) {
	do {
		if (player.getPos() - posCreate > Pipeline_Part_CMR::NB_POINTS / 2) {
			try {
				posCreate += Pipeline_Part_CMR::NB_POINTS;
				tuyau->addNewPart(loader);
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
	return;
}



int App_Runner::init() {
	Viewer::init();

	score = create_text();

	//Create thread to create and request delete part of the pipe
	thread_PipeBuilder = std::thread(createPartIfNeeded, std::ref(player), std::ref(tuyau), std::ref(loader));



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
	Viewer::quit();

	// etape 3 : detruire la description du triangle
	continuCreate = false;

	loader.release();

	player.getObject().release();

	if (thread_PipeBuilder.joinable())
		thread_PipeBuilder.join();

	release_text(score);

	return 0;   // ras, pas d'erreur
}












/**
	@Param time temps depuis le lancement de l'app (en ms)
	@Param delta temps depuis l'image precedante (en ms)
*/
int App_Runner::update(const float time, const float delta) {
	float fps = 60;

	// Prevent Jump when delta too big
	if (delta < 1000) {
		fps = FPS::getFPS(delta);
	}

	//std::cout << "time:" << time << "  delta:" << delta << "  FPS:" << fps << "\n";

	scoreValue += delta / 100.f;

	// Player Action
	player.action(fps, tuyau);

	// Delete part if requested
	tuyau->deleteLastPart();

	// Collsion of the player with other box
	collision();


	// Score text 
	clear(score);
	std::string textScore = "Score: ";
	textScore.append(std::to_string((int)scoreValue));
	print(score, 70, 1, textScore.c_str());

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


		std::vector<ObstacleObj*> list_O = p->getObstacles();
		for (int i = 0; i < list_O.size(); i++) {
			drawer.draw(player.getCamera(), *list_O.at(i)->getMeshObject(), list_O.at(i)->getHitBox().T, *list_O.at(i)->getTriangleGroupe());
		}


		std::vector<BonusObj*> list_B = p->getBonus();
		for (int i = 0; i < list_B.size(); i++) {
			if (!list_B.at(i)->haveBeenTaken()) {
				drawer.draw(player.getCamera(), *list_B.at(i)->getMeshObject(), list_B.at(i)->getHitBox().T, *list_B.at(i)->getTriangleGroupe());
			}
		}
		//draw(*nbPartCreated->get(), Identity(), camera.get_Camera(), camera.get_Projection());
	}

	drawer.draw(player.getCamera(), player.getObject(), player.getObjModel(), player.getGroupeTriangle());

	draw(score, window_width(), window_height());

	return 1;
}


static void detectCollision_Obstacles(Player& player, Box& play, float* scoreValue, std::vector<ObstacleObj*>& list_C) {
	for (int i = 0; i < list_C.size(); i++) {
		if (play.collides(list_C[i]->getBonusHitBox())) {
			if (play.collides(list_C[i]->getHitBox())) {
				std::cout << "Colision" << std::endl;
				player.stopSpeed();
				*scoreValue = 0;
			}
			else {
				std::cout << "Bonus Close" << std::endl;
				*scoreValue += 100;
			}
		}
	}
}

static void detectCollsion_Bonus(Player& player, Box& play, float* scoreValue, std::vector<BonusObj*>& list_B) {
	for (int i = 0; i < list_B.size(); i++) {
		if (!list_B[i]->haveBeenTaken()) {
			if (play.collides(list_B[i]->getHitBox())) {
				list_B[i]->take();
				std::cout << "Bonus Block" << std::endl;
				*scoreValue += 250;
			}
		}
	}
}


void App_Runner::collision() {
	Box play = player.getCollision();

	detectCollision_Obstacles(player, play, &scoreValue, tuyau->getPart()[0]->getObstacles());
	detectCollision_Obstacles(player, play, &scoreValue, tuyau->getPart()[1]->getObstacles());

	detectCollsion_Bonus(player, play, &scoreValue, tuyau->getPart()[0]->getBonus());
	detectCollsion_Bonus(player, play, &scoreValue, tuyau->getPart()[1]->getBonus());
}






