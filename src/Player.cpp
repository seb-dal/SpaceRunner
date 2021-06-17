#include "runner/include/Player.h"

const float Player::vitesseRot = 2.5;
const float Player::vitMax = 1.5;

const int Player::ms_Hit_Anim = 200;

Player::Player(MeshLoader& loader, const float sizePipe, const float zoom) {
	camera = Camera(window_width(), window_height(), 70, sizePipe * (5 / zoom), sizePipe * (400 / zoom));

	object = &loader.Player.objMesh;
	groups = &loader.Player.groups;

	colision = Box(loader.Player.bounds.pmin, loader.Player.bounds.pmax);

}



Player::~Player() {
}


static Transform sc_HitBox = Scale(3.5);
static Transform sc_Object = Scale(4);
static Transform rot_defaultObject = RotationY(90);

void Player::action(float TotalTime, float fps, Pipeline* pipe) {
	if (key_state(SDLK_LEFT) || key_state(SDLK_q))
		rotationCircule = std::fmod(rotationCircule + vitesseRot * (60 / fps) + 360, 360);
	if (key_state(SDLK_RIGHT) || key_state(SDLK_d))
		rotationCircule = std::fmod(rotationCircule - vitesseRot * (60 / fps) + 360, 360);


	//if (key_state(SDLK_UP) || key_state(SDLK_z))
	pos += vitesse * (60 / fps);
	vitesse = std::min(vitMax, vitesse + (60 / fps) * (0.01f / (vitesse * vitesse + 1)));

	camera.setRatio(window_width(), window_height());

	float posPlayer = pos + Pipeline_Part_CMR::NB_POINTS / 2;

	camera.lookAt(
		Utility::rotAround(
			pipe->getPosition(pos),
			pipe->getSizePipe() * 8,
			pipe->getAxe(pos),
			normalize(pipe->getNormal(pos)),
			rotationCircule
		),
		Utility::rotAround(
			pipe->getPosition(posPlayer),
			pipe->getSizePipe() * 1,
			pipe->getAxe(posPlayer),
			normalize(pipe->getNormal(posPlayer)),
			rotationCircule
		),
		Rotation(pipe->getAxe(pos + 1), rotationCircule)(pipe->getNormal(pos + 1))
	);


	objModel = Utility::modelOnPipe(
		pipe,
		posPlayer,
		pipe->getSizePipe() * 1.5,
		rotationCircule
	)(rot_defaultObject);

	colision.T = objModel;

	colision.T = colision.T(sc_HitBox);
	objModel = objModel(sc_Object);

	if (HIT_Animation > 0) {
		if (HIT_When / ms_Hit_Anim + 1 <= (int)TotalTime / ms_Hit_Anim) {
			HIT_When = TotalTime; // update HIT_when to wait for an other change
			HIT_Animation--;
		}
	}

}



float Player::getPos() { return pos; }


/*void Player::decreasePos(const float dec) {
	pos -= dec;
}*/

Camera& Player::getCamera() { return camera; }



Mesh& Player::getObject() { return *object; }



Transform& Player::getObjModel() { return objModel; }



std::vector<TriangleGroup>& Player::getGroupeTriangle() { return *groups; }



Box& Player::getCollision() { return colision; }



void Player::stopSpeed() { vitesse = 0; }



int Player::getHIT_Animation() { return HIT_Animation; }



void Player::hitObstacle(float when) {
	health--;
	HIT_Animation = 10;
	HIT_When = when;
}



int Player::getHealth() { return health; }



void Player::collectBonus(float* scoreValue) {
	bonusCollect++;
	if (bonusCollect >= 100) {//if the player manage to collect 100 bonus, he gain 1 health 
		if (health < 5) {
			health += 1;
		}
		else {
			*scoreValue += 100000;//if the player manage to keep 5 health and get 100 bonus, he obtain a huge score bonus
		}
		bonusCollect -= 100;
	}
}




int Player::getCollectedBonus() { return bonusCollect; }




void Player::reset() {
	// reset all values
	health = 3;
	bonusCollect = 0;
	rotationCircule = 0;
	vitesse = 0;
	pos = 10;
	HIT_Animation = 0;
	HIT_When = 0;
}

