#pragma once

#include <vector>
#include <src/gKit/mesh.h>
#include <runner/include/box.hpp>
#include <runner/include/MeshLoader.h>

/**
 * Abstract class for pipe Object.
 */
class Pipe_Object {
public:
	/**
	 * Get the hitbox of the Object.
	 *
	 * \return hitbox
	 */
	Box& getHitBox();

	/**
	 * Get Mesh of the Object.
	 *
	 * \return Mesh
	 */
	Mesh* getMeshObject();
	/**
	 * get the list of TriangleGroup for colored draw.
	 *
	 * \return list of TriangleGroup
	 */
	std::vector<TriangleGroup>* getTriangleGroupe();

	/**
	 * Get the transform of the Object (position/roattion/scale).
	 *
	 * \return Matrix of the Object
	 */
	Transform& getModel();

protected:

	Transform ModelMesh;
	Box HitBox;

	// Pointer (avoid useless copy)
	Mesh* object;
	std::vector<TriangleGroup>* groups_Obj;
};
