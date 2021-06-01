#pragma once

#include <vector>
#include <src/gKit/mesh.h>
#include <src/gKit/wavefront.h>

class ColoredMesh {
public:
	ColoredMesh(const char* filename) {
		object = read_mesh(filename);
		groups = object.groups();
	}

	void release() {
		object.release();
		groups.clear();
	}

	Mesh object;
	std::vector<TriangleGroup> groups;
};
