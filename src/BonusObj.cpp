#include "runner/include/BonusObj.h"

const Transform BonusObj::scale_collsionBoxBonus = Scale(2.2);
const Transform BonusObj::scale_model = Scale(1.6);

static const Vector axesRotation(1.f / 3.f, 2.f / 3.f, 1);
static const float angleRotate = 7.5;
const Transform BonusObj::rotation_Animation = Rotation(axesRotation, angleRotate);


BonusObj::BonusObj(MeshLoader& loader, Transform& T) {
	object = &loader.Bonus.objMesh;
	groups_Obj = &loader.Bonus.groups;

	HitBox = Box(loader.Bonus.bounds.pmin, loader.Bonus.bounds.pmax);
	HitBox.T = T;

	ModelMesh = HitBox.T(scale_model);

	HitBox.T = HitBox.T(scale_collsionBoxBonus);

	taken = false;
}



void BonusObj::take() { taken = true; }



bool BonusObj::haveBeenTaken() { return taken; }



void BonusObj::Rotate() { ModelMesh = ModelMesh(rotation_Animation); }


