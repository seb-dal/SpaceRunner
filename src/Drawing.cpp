#include <runner/include/Drawing.h>

Drawing::Drawing() {
}

void Drawing::draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection, const GLuint texture) {
	param.model(model).view(view).projection(projection);
	param.texture(texture);
	param.draw(m);
}

void Drawing::draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection) {
	param.model(model).view(view).projection(projection);
	param.draw(m);
}

void Drawing::draw(Mesh& m, const Transform& model, const Transform& view, const Transform& projection, std::vector<TriangleGroup>& group) {
	param.model(model).view(view).projection(projection);
	for (int i = 0; i < group.size(); i++) {
		param.draw(group[i], m);
	}
}

void Drawing::draw(Camera& cam, Mesh& obj, Transform& scale, const GLuint texture) {
	draw(obj, scale, cam.get_Camera(), cam.get_Projection(), texture);
}

void Drawing::draw(Camera& cam, Mesh& obj, Transform& model) {
	draw(obj, model, cam.get_Camera(), cam.get_Projection());
}

void Drawing::draw(Camera& cam, Mesh& obj, Transform& model, std::vector<TriangleGroup>& group) {
	draw(obj, model, cam.get_Camera(), cam.get_Projection(), group);
}

void Drawing::light(Point& light) {
	param.lighting();
	param.light(light);
}
