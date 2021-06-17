#pragma once
#include "runner/include/Pipe_Object.h"



class ObstacleObj : public Pipe_Object {
public:

	ObstacleObj(MeshLoader& loader, Transform& T);

	Box& getBonusHitBox();

	bool getHitted();
	void hitted();
private:
	static const Transform scale_collsionBoxBonus;
	static const Transform scale_CollisionBox;
	static const Transform scale_model;

	//==============================
	Box Bonus_HitBox;
	bool hit;
};
