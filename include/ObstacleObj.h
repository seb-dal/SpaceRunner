#pragma once
#include "runner/include/Pipe_Object.h"



class ObstacleObj : public Pipe_Object {
public:

	ObstacleObj(MeshLoader& loader, Transform& T);

	Box& getBonusHitBox();

	bool getHitted();
	void hitted();
private:
	static const float scale_collsionBoxBonus;
	static const float scale_CollisionBox;
	static const float scale_model;

	//==============================
	Box Bonus_HitBox;
	bool hit;
};
