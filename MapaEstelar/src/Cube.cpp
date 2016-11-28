#include "Cube.h"

#include <vector>
#include <iostream>

#include <GL\glew.h>

const Point vertex[] = {
	{ 1, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, -1, 1, 1, 1, 0, 0, 1 },
	{ 1, 1, -1, 1, 1, 0, 0, 1 },
	{ 1, -1, -1, 1, 1, 0, 0, 1 },
	{ 1, -1, 1, 1, 1, 0, 0, 1 },
	{ 1, 1, -1, 1, 1, 0, 0, 1 },

	{ -1, 1, 1, 1, 0, 1, 0, 1 },
	{ -1, -1, 1, 1, 0, 1, 0, 1 },
	{ -1, 1, -1, 1, 0, 1, 0, 1 },
	{ -1, -1, -1, 1, 0, 1, 0, 1 },
	{ -1, -1, 1, 1, 0, 1, 0, 1 },
	{ -1, 1, -1, 1, 0, 1, 0, 1 },
};

Cube::Cube(RenderSystem* sys) :
	GraphicComponent(sys),
	data_buffer(0) {
	program = GLProgram::getProgram("star");

	if (data_buffer == 0) {
		glGenBuffers(1, &data_buffer);
	}

	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(4);
}

int Cube::update() {
	return 1;
}

int Cube::render() {
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUseProgram(program->id);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, position));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, color));
	//glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, size));

	glUniformMatrix4fv(program->uniform["world_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->world_matrix[0][0]));
	glUniformMatrix4fv(program->uniform["camera_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->camera_matrix[0][0]));

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	return 1;
}