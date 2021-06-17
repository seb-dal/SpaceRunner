#include "runner/include/ObstacleObj.h"

const Transform ObstacleObj::scale_collsionBoxBonus = Scale(2.6);
const Transform ObstacleObj::scale_CollisionBox = Scale(1.1);
const Transform ObstacleObj::scale_model = Scale(1.3);


ObstacleObj::ObstacleObj(MeshLoader& loader, Transform& T) {
	hit = false;
	object = &loader.Obstacle.objMesh;
	groups_Obj = &loader.Obstacle.groups;


	HitBox = Box(loader.Obstacle.bounds.pmin, loader.Obstacle.bounds.pmax);
	HitBox.T = T;
	Bonus_HitBox = Box(HitBox);

	ModelMesh = HitBox.T(scale_model);

	HitBox.T = HitBox.T(scale_CollisionBox);
	int r = rand() % 4; // change which face of the obstacle the player will see 
	HitBox.T = HitBox.T(RotationY(90 * r));

	Bonus_HitBox.T = Bonus_HitBox.T(scale_collsionBoxBonus);
}



Box& ObstacleObj::getBonusHitBox() { return Bonus_HitBox; }



bool ObstacleObj::getHitted() { return hit; }



void ObstacleObj::hitted() { hit = true; }


