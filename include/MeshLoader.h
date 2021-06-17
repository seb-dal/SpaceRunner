#pragma once
#include <src/gKit/mesh.h>
#include <src/gKit/wavefront.h>
#include <src/gKit/texture.h>



struct BoundsPointsMesh {
	Point pmin, pmax;
};


/**
 * Compute only Once all Mesh elements that will be use later.
 */
struct MeshOBJ {
	Mesh objMesh;

	// to draw the Mesh with material color
	std::vector<TriangleGroup> groups;

	// Points de la boite englobante
	BoundsPointsMesh bounds;

	MeshOBJ() {}
	MeshOBJ(Mesh& obj) {
		objMesh = obj;
		groups = objMesh.groups();
		objMesh.bounds(bounds.pmin, bounds.pmax);
	}

	void clear() {
		objMesh.release();
		groups.clear();
	}
};

/**
 * Load all the Mesh object of the application.
 */
class MeshLoader {
public:
	MeshLoader() {
		Bonus = MeshOBJ(read_mesh("runner/data/Piece4.obj"));
		Obstacle = MeshOBJ(read_mesh("runner/data/Piece2.obj"));
		Player = MeshOBJ(read_mesh("runner/data/Piece1.obj"));

		textPipe = read_texture(0, "runner/data/pipe.jpg");
	}

	void release() {
		Bonus.clear();
		Obstacle.clear();
		Player.clear();
	}

	// public Objects/Textures
	// vector<TriangleGroup> for drawing with material colors
	MeshOBJ Bonus;
	MeshOBJ Obstacle;
	MeshOBJ Player;

	GLuint textPipe;
};
