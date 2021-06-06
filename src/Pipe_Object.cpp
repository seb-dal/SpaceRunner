#include "runner/include/Pipe_Object.h"

Box& Pipe_Object::getHitBox() { return HitBox; }

Mesh* Pipe_Object::getMeshObject() { return object; }

std::vector<TriangleGroup>* Pipe_Object::getTriangleGroupe() { return groups_Obj; }

Transform& Pipe_Object::getModel() { return ModelMesh; }