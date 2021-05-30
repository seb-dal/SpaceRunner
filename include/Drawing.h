#pragma once

#include <runner/include/Camera.h>
#include <src/gKit/draw.h>

class Drawing {
	DrawParam param;
public:
	Drawing();

	void draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection, const GLuint texture);

	void draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection);

	void draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection, std::vector<TriangleGroup>& group);




	void draw(Camera& cam, Mesh& obj, Transform& scale, const GLuint texture);

	void draw(Camera& cam, Mesh& obj, Transform& model);

	void draw(Camera& cam, Mesh& obj, Transform& model, std::vector<TriangleGroup>& group);

	void light(Point& light);


};
