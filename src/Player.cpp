#include "runner/include/Player.h"

const float Player::vitesseRot = 2.5;
const float Player::vitMax = 1.5;

Player::Player(MeshLoader& loader, const float sizePipe, const float zoom) {
	camera = Camera(window_width(), window_height(), 70, sizePipe * (5 / zoom), sizePipe * (400 / zoom));

	object = loader.Play;
	groups = loader.groups_Play;

	Point pmin, pmax;
	object.bounds(pmin, pmax);
	colision = Box(pmin, pmax);

}

Player::~Player() {
	object.release();
}

void Player::action(float fps, Pipeline* pipe) {
	if (key_state(SDLK_LEFT) || key_state(SDLK_q))
		rotationCircule = std::fmod(rotationCircule + vitesseRot * (60 / fps) + 360, 360);
	if (key_state(SDLK_RIGHT) || key_state(SDLK_d))
		rotationCircule = std::fmod(rotationCircule - vitesseRot * (60 / fps) + 360, 360);


	//if (key_state(SDLK_UP) || key_state(SDLK_z))
	pos += vitesse * (60 / fps);
	vitesse = std::min(vitMax, vitesse + (60 / fps) * (0.01f / (1000000 * vitesse * vitesse)));

	camera.setRatio(window_width(), window_height());

	camera.lookAt(
		Utility::rotAround(
			pipe->getPosition(pos),
			pipe->getSizePipe() * 8,
			pipe->getAxe(pos),
			normalize(pipe->getNormal(pos)),
			rotationCircule
		),
		Utility::rotAround(
			pipe->getPosition(pos + Pipeline_Part_CMR::NB_POINTS / 2),
			pipe->getSizePipe() * 1,
			pipe->getAxe(pos + Pipeline_Part_CMR::NB_POINTS / 2),
			normalize(pipe->getNormal(pos + Pipeline_Part_CMR::NB_POINTS / 2)),
			rotationCircule
		),
		Rotation(pipe->getAxe(pos + 1), rotationCircule)(pipe->getNormal(pos + 1))
	);



	/*objModel = Identity();

	objModel = objModel(Translation(Vector(Utility::rotAround(
		pipe->getPosition(pos + Pipeline_Part_CMR::NB_POINTS / 2),
		pipe->getSizePipe() * 1.5,
		pipe->getAxe(pos + Pipeline_Part_CMR::NB_POINTS / 2),
		pipe->getNormal(pos + Pipeline_Part_CMR::NB_POINTS / 2),
		rotationCircule))
	));
	objModel = objModel(Rotation(pipe->getAxe(pos + Pipeline_Part_CMR::NB_POINTS / 2), rotationCircule));
	objModel = objModel(Rotation(Vector(-1, 0, 0), pipe->getAxe(pos + Pipeline_Part_CMR::NB_POINTS / 2)));*/

	objModel = Utility::modelOnPipe(
		pipe,
		pos + Pipeline_Part_CMR::NB_POINTS / 2,
		pipe->getSizePipe() * 1.5,
		rotationCircule
	)(RotationY(90));

	colision.T = objModel;

	colision.T = colision.T(Scale(3.5));
	objModel = objModel(Scale(4));

}

float Player::getPos() { return pos; }

/*void Player::decreasePos(const float dec) {
	pos -= dec;
}*/

Camera& Player::getCamera() { return camera; }

Mesh& Player::getObject() { return object; }

Transform& Player::getObjModel() { return objModel; }

std::vector<TriangleGroup>& Player::getGroupeTriangle() {
	return groups;
}

Box Player::getCollision() {
	return colision;
}

void Player::stopSpeed() {
	vitesse = 0;
}

