#include "runner/include/ObstacleObj.h"

const float ObstacleObj::scale_collsionBoxBonus = 2.6;
const float ObstacleObj::scale_CollisionBox = 1.3;


ObstacleObj::ObstacleObj(MeshLoader& loader, Transform& T) {
	object = &loader.Obstacle;
	groups_Obj = &loader.groups_Obstacle;

	Point pmin, pmax;
	object->bounds(pmin, pmax);

	HitBox = Box(pmin, pmax);
	HitBox.T = T;
	Bonus_HitBox = Box(HitBox);

	HitBox.T = HitBox.T(Scale(scale_CollisionBox));
	Bonus_HitBox.T = Bonus_HitBox.T(Scale(scale_collsionBoxBonus));
}

Box& ObstacleObj::getBonusHitBox() {
	return Bonus_HitBox;
}
