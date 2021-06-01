#pragma once

#include "runner/include/Pipe_Object.h"


class BonusObj : public Pipe_Object {
public:

	BonusObj(MeshLoader& loader, Transform& T);

	void take();
	bool haveBeenTaken();

	void Rotate(const Vector& v, const float angle);

private:
	static const float scale_collsionBoxBonus;
	static const float scale_model;

	//==============================
	bool taken;

};
