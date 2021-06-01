#include "runner/include/ObstacleObj.h"

const float ObstacleObj::scale_collsionBoxBonus = 2.6;
const float ObstacleObj::scale_CollisionBox = 1.1;
const float ObstacleObj::scale_model = 1.3;

ObstacleObj::ObstacleObj(MeshLoader& loader, Transform& T) {
	object = &loader.Obstacle;
	groups_Obj = &loader.groups_Obstacle;

	Point pmin, pmax;
	object->bounds(pmin, pmax);

	HitBox = Box(pmin, pmax);
	HitBox.T = T;
	Bonus_HitBox = Box(HitBox);

	ModelMesh = HitBox.T(Scale(scale_model));

	HitBox.T = HitBox.T(Scale(scale_CollisionBox));
	int r = rand() % 4;
	HitBox.T = HitBox.T(RotationY(90 * r));

	Bonus_HitBox.T = Bonus_HitBox.T(Scale(scale_collsionBoxBonus));
}

Box& ObstacleObj::getBonusHitBox() {
	return Bonus_HitBox;
}
