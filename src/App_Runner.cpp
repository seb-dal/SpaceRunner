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

/**
 * Create a new pipe part if needed.
 * LOOP for multi thread use (one only)
 *
 * \param player player
 * \param tuyau Pipe
 * \param loader Meshloader
 */
static void createPartIfNeeded(Player& player, Pipeline* tuyau, MeshLoader& loader) {
	float mid = Pipeline_Part_CMR::NB_POINTS / 2;
	do {
		if (player.getPos() - posCreate > mid) {
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

	} while (continuCreate);
	return;
}



int App_Runner::init() {
	Viewer::init();

	score = create_text();
	fpsDisplay = create_text();

	gameoverDiplay = create_text();
	print(gameoverDiplay, 65, 6, "          GAME OVER\n\n\n Press 'R' to restart the game");
	gameoverDiplay.color = Red();


	//Create thread to create and request delete part of the pipe
	thread_PipeBuilder = std::thread(createPartIfNeeded, std::ref(player), std::ref(tuyau), std::ref(loader));



	// etat openGL par defaut
	//glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
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
	release_text(fpsDisplay);
	release_text(gameoverDiplay);

	return 0;   // ras, pas d'erreur
}








/**
 * Rotate the bonus box.
 *
 * \param list_B list of Bonus box
 */
static void rotationBonus(std::vector<BonusObj*>& list_B) {
	int i;
	for (i = 0; i < list_B.size(); i++) {
		if (!list_B[i]->haveBeenTaken()) {
			list_B[i]->Rotate();
		}
	}
}



/**
	@Param time temps depuis le lancement de l'app (en ms)
	@Param delta temps depuis l'image precedante (en ms)
*/
int App_Runner::update(const float time, const float delta) {
	float fps = 60;

	// Prevent Jump position when delta too big
	if (delta < 1000) {
		fps = FPS::getFPS(delta);
	}

	//std::cout << "time:" << time << "  delta:" << delta << "  FPS:" << fps << "\n";
	if (!gameover) {
		scoreValue += delta / 100.f;

		// Player Action
		player.action(time, fps, tuyau);

		// Delete part if requested
		tuyau->deleteLastPart();

		//Animation Bonus Box
		std::vector<Pipeline_Part_CMR*> parts = tuyau->getPart();
		int i;
		for (i = 0; i < 6; i++)
			rotationBonus(parts[i]->getBonus());


		// Collsion of the player with other box
		collision(time, delta);
	}
	else {
		if (key_state(SDLK_r) || key_state(SDLK_INSERT)) {
			// Reset after GAMEOVER
			continuCreate = false;
			if (thread_PipeBuilder.joinable())
				thread_PipeBuilder.join();

			delete tuyau;
			tuyau = new Pipeline(loader, sizePipe, 32);
			player.reset();

			posCreate = 100;
			continuCreate = true;
			thread_PipeBuilder = std::thread(createPartIfNeeded, std::ref(player), std::ref(tuyau), std::ref(loader));

			gameover = false;
			scoreValue = 0;
		}
	}


	// Score text 
	clear(score);
	std::string textScore;

	textScore.append("Health: "); // Number of Health points
	int i;
	for (i = 0; i < player.getHealth(); i++) {
		textScore.append("O ");
	}

	textScore.append("\n");

	textScore.append("Bonus collected: ");
	textScore.append(std::to_string(player.getCollectedBonus()));

	textScore.append("\n");

	textScore.append("   Score: ");
	textScore.append(std::to_string((int)scoreValue));

	print(score, 70, 1, textScore.c_str());

	clear(fpsDisplay);
	std::string fpstext;
	fpstext.append(std::to_string((int)fps));
	print(fpsDisplay, 120, 1, fpstext.c_str());

	return 0;
}






int App_Runner::render() {
	Drawing drawer;
	int i;
	// etape 2 : dessiner l'objet avec opengl
	// on commence par effacer la fenetre avant de dessiner quelquechose
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// on efface aussi le zbuffer
	if (!gameover) {
		//draw(objet, Transform(), camera.get_Camera(), camera.get_Projection());
		for (Pipeline_Part_CMR* p : tuyau->getPart()) {
			// draw PIPE FRAGMENT
			drawer.draw(player.getCamera(), *p->get(), Identity(), loader.textPipe);


			std::vector<ObstacleObj*> list_O = p->getObstacles();
			for (i = 0; i < list_O.size(); i++) {
				// draw OBSTACLE
				drawer.draw(player.getCamera(), *list_O.at(i)->getMeshObject(), list_O.at(i)->getModel(), *list_O.at(i)->getTriangleGroupe());
			}


			std::vector<BonusObj*> list_B = p->getBonus();
			for (i = 0; i < list_B.size(); i++) {
				if (!list_B.at(i)->haveBeenTaken()) {
					// draw BONUS
					drawer.draw(player.getCamera(), *list_B.at(i)->getMeshObject(), list_B.at(i)->getModel(), *list_B.at(i)->getTriangleGroupe());
				}
			}
			//draw(*nbPartCreated->get(), Identity(), camera.get_Camera(), camera.get_Projection());
		}

		// draw PLAYER
		if (player.getHIT_Animation() % 2 == 0) {
			drawer.draw(player.getCamera(), player.getObject(), player.getObjModel(), player.getGroupeTriangle());
		}
	}

	//draw TEXTS
	draw(score, window_width(), window_height());
	draw(fpsDisplay, window_width(), window_height());

	if (gameover) {
		//draw GAMEOVER TEXT
		draw(gameoverDiplay, window_width(), window_height());
	}

	return 1;
}



/**
 * Detect Collision with obstacle (Bonus + Collision).
 *
 * \param player player object
 * \param play collision box of the player
 * \param scoreValue pointer to ScoreValue
 * \param list_C list of Obstacle
 */
static void detectCollision_Obstacles(float time, Player& player, Box& play, float* scoreValue, std::vector<ObstacleObj*>& list_C) {
	int i, max = list_C.size();
	for (i = 0; i < max; i++) {
		if (play.collides(list_C[i]->getBonusHitBox())) {
			if (play.collides(list_C[i]->getHitBox())) {
				if (!list_C[i]->getHitted()) { //health decrease only count once
					player.stopSpeed();

					std::cout << "Colision" << std::endl;
					player.hitObstacle(time);
					list_C[i]->hitted();

					*scoreValue = std::max(*scoreValue - 1000, 0.f);//penality for staying on obstacle
				}

			}
			else {
				if (!list_C[i]->getHitted()) {//avoir getting point when Obstacle touch
					std::cout << "Bonus Close" << std::endl;
					*scoreValue += 100; //pass close to obstacle
				}
			}
		}
	}
}

/**
 * Detect collision with Bonus Box.
 *
 * \param player player object
 * \param play collision box of the player
 * \param scoreValue pointer to ScoreValue
 * \param list_B list of Bonus box
 */
static void detectCollsion_Bonus(Player& player, Box& play, float* scoreValue, std::vector<BonusObj*>& list_B) {
	int i, max = list_B.size();
	for (i = 0; i < max; i++) {
		if (!list_B[i]->haveBeenTaken()) {
			if (play.collides(list_B[i]->getHitBox())) {
				list_B[i]->take();

				std::cout << "Bonus Block" << std::endl;
				player.collectBonus(scoreValue);
				*scoreValue += 250;
			}
		}
	}
}




void App_Runner::collision(float time, float delta) {
	Box play = player.getCollision();

	std::vector<Pipeline_Part_CMR*> parts = tuyau->getPart();

	// detect colition with the objects with the 4 first fragments of the Pipe only
	int i;
	for (i = 1; i < 4; i++)
		detectCollision_Obstacles(time, player, play, &scoreValue, parts[i]->getObstacles());

	if (player.getHealth() < 0) {
		gameover = true;
		continuCreate = false; // stop the thread which create pipe fragment
	}

	for (i = 1; i < 4; i++)
		detectCollsion_Bonus(player, play, &scoreValue, parts[i]->getBonus());

}






