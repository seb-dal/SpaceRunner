#pragma once

#include "runner/include/Pipe_Object.h"


class BonusObj : public Pipe_Object {
public:

	BonusObj(MeshLoader& loader, Transform& T);

	/**
	 * Take the bonus.
	 *
	 */
	void take();
	bool haveBeenTaken();

	/**
	 * Animate the bonus by rotating it.
	 *
	 * \param v vector around which the bonus will rotate
	 * \param angle angle of rotation
	 */
	void Rotate(const Vector& v, const float angle);

private:
	static const float scale_collsionBoxBonus;
	static const float scale_model;

	//==============================
	bool taken;

};
