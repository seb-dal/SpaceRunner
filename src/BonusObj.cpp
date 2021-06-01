#include "runner/include/BonusObj.h"

const float BonusObj::scale_collsionBoxBonus = 1.6;


BonusObj::BonusObj(MeshLoader& loader, Transform& T) {
	object = &loader.Bonus;
	groups_Obj = &loader.groups_Bonus;

	Point pmin, pmax;
	object->bounds(pmin, pmax);

	HitBox = Box(pmin, pmax);
	HitBox.T = T;

	HitBox.T = HitBox.T(Scale(scale_collsionBoxBonus));

	taken = false;
}

void BonusObj::take() {
	taken = true;
}

bool BonusObj::haveBeenTaken() {
	return taken;
}
