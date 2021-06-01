#pragma once

#include <vector>
#include <src/gKit/mesh.h>
#include <runner/include/box.hpp>
#include <runner/include/MeshLoader.h>


class Pipe_Object {
public:

	Box& getHitBox();

	Mesh* getMeshObject();
	std::vector<TriangleGroup>* getTriangleGroupe();

	Transform& getModel();

protected:

	Transform ModelMesh;

	Box HitBox;

	Mesh* object;
	std::vector<TriangleGroup>* groups_Obj;
};
