#pragma once

#include <vector>
#include <src/gKit/mesh.h>
#include <box-intersection-etu/box.hpp>
#include <runner/include/MeshLoader.h>


class Pipe_Object {
public:

	Box& getHitBox();

	Mesh* getMeshObject();
	std::vector<TriangleGroup>* getTriangleGroupe();

protected:

	Box HitBox;
	Mesh* object;
	std::vector<TriangleGroup>* groups_Obj;
};
