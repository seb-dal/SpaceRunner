#pragma once

#include "runner/include/Pipe_Object.h"


class BonusObj : public Pipe_Object {
public:

	BonusObj(MeshLoader& loader, Transform& T);

	void take();
	bool haveBeenTaken();

private:
	static const float scale_collsionBoxBonus;

	//==============================
	bool taken;

};
