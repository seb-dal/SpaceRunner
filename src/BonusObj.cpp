#include "runner/include/BonusObj.h"

const float BonusObj::scale_collsionBoxBonus = 2.2;
const float BonusObj::scale_model = 1.6;

BonusObj::BonusObj(MeshLoader& loader, Transform& T) {
	object = &loader.Bonus;
	groups_Obj = &loader.groups_Bonus;

	Point pmin, pmax;
	object->bounds(pmin, pmax);

	HitBox = Box(pmin, pmax);
	HitBox.T = T;

	ModelMesh = HitBox.T(Scale(scale_model));

	HitBox.T = HitBox.T(Scale(scale_collsionBoxBonus));

	taken = false;
}

void BonusObj::take() {
	taken = true;
}

bool BonusObj::haveBeenTaken() {
	return taken;
}

Transform& BonusObj::getModel() {
	return ModelMesh;
}

void BonusObj::Rotate(const Vector& v, const float angle) {
	ModelMesh = ModelMesh(Rotation(v, angle));
}
