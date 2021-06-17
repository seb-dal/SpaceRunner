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
	 */
	void Rotate();

private:
	static const Transform scale_collsionBoxBonus;
	static const Transform scale_model;
	static const Transform rotation_Animation;

	//==============================
	bool taken;

};
