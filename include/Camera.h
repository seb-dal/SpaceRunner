#pragma once
#include <src/gKit/mat.h>

class Camera {
	float fov;
	float height, width;
	float znear, zfar;
protected:
	Transform cam, proj;

	/**
	 * Calcule la matrice de projection.
	 *
	 * \param fov field of view
	 * \param aspect ratio de la fenettre (16/9)
	 * \param znear profondeur proche
	 * \param zfar profondeur loin
	 */
	void projection(const float fov, const float aspect, const float znear, const float zfar) {
		proj = Perspective(fov, aspect, znear, zfar);
	}

public:
	Camera() {}

	/**
	 * Création d'une camera simple.
	 *
	 * \param width longeur de la fenetre
	 * \param height hauteur de la fenetre
	 * \param fov field of view
	 * \param znear profondeur proche
	 * \param zfar profondeur loin
	 */
	Camera(
		const int width, const int height,
		const float fov,
		const float znear, const float zfar
	) :fov(fov), height(height), width(width), znear(std::max(0.1f, znear)), zfar(std::max(1.f, zfar)) {
		projection(fov, width / height, znear, zfar);
	}

	/**
	 * .
	 *
	 * \param width
	 * \param height
	 */
	void setRatio(const int width, const int height) {
		this->width = width;
		this->height = height;
		projection(fov, this->width / this->height, znear, zfar);
	}

	/**
	 * Change le FOV de la matrive de projection.
	 *
	 * \param fov field of view
	 */
	void setFOV(const float fov) {
		this->fov = fov;
		projection(fov, width / height, znear, zfar);
	}

	/**
	 * Change la profondeur de vus.
	 *
	 * \param znear profondeur proche
	 * \param zfar profondeur loin
	 */
	void setZnear_Zfar(const float znear, const float zfar) {
		this->znear = znear;
		this->zfar = zfar;
		projection(fov, width / height, znear, zfar);
	}


	/**
	 * Calcule la matrice pour la position de la camera et là où elle regarde.
	 *
	 * \param from position de la camera
	 * \param to position du point observé
	 * \param up Vecteur de rotation autour de l'axe entre "from" et "to"
	 */
	void lookAt(const Point& from, const Point& to, const Vector& up) {
		cam = Lookat(from, to, normalize(up));
	}

	Transform& get_Projection() {
		return proj;
	}

	Transform& get_Camera() {
		return cam;
	}
};