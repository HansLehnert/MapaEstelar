#pragma once

#include <GL\glew.h>

class GLMesh {
public:
	GLuint vertex_buffer;
	GLuint index_buffer;

	int vertex_length;
	int index_length;
};