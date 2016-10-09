#pragma once

#include <vector>

#include <GL\glew.h>

#include "display\GraphicComponent.h"

struct Star {
	struct {
		float x;
		float y;
		float z;
		float w;
	} position;

	struct {
		float r;
		float g;
		float b;
	} color;

	float size;
};

class StarSet : public GraphicComponent {
public:
	StarSet(RenderSystem*);

	int update();
	int load(std::vector<Star>);

private:
	GLuint data_buffer;

	int n_data;
};