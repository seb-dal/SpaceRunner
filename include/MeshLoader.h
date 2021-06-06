#pragma once
#include <src/gKit/mesh.h>
#include <src/gKit/wavefront.h>
#include <src/gKit/texture.h>

/**
 * Load all the Mesh object of the application.
 */
class MeshLoader {
public:
	MeshLoader() {
		Bonus = read_mesh("runner/data/Piece4.obj");
		Obstacle = read_mesh("runner/data/Piece2.obj");
		Play = read_mesh("runner/data/Piece1.obj");

		groups_Bonus = Bonus.groups();
		groups_Obstacle = Obstacle.groups();
		groups_Play = Play.groups();

		textPipe = read_texture(0, "runner/data/pipe.jpg");
	}

	void release() {
		Bonus.release();
		Obstacle.release();
		Play.release();

		groups_Bonus.clear();
		groups_Obstacle.clear();
		groups_Play.clear();
	}

	Mesh Bonus;
	std::vector<TriangleGroup> groups_Bonus;

	Mesh Obstacle;
	std::vector<TriangleGroup> groups_Obstacle;

	Mesh Play;
	std::vector<TriangleGroup> groups_Play;

	GLuint textPipe;
};
