#include "StarSet.h"

#include <vector>
#include <iostream>

#include <GL\glew.h>

StarSet::StarSet(RenderSystem* sys) :
	GraphicComponent(sys),
	data_buffer(0) {
	program = GLProgram::getProgram("star");
}

int StarSet::update() {
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUseProgram(program->id);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Star), 0);

	glUniformMatrix4fv(program->world_loc, 1, GL_FALSE, &(((RenderSystem*)system)->world_matrix[0][0]));
	glUniformMatrix4fv(program->camera_loc, 1, GL_FALSE, &(((RenderSystem*)system)->camera_matrix[0][0]));

	glDrawArrays(GL_POINTS, 0, n_data);

	return 1;
}

int StarSet::load(std::vector<Star> data) {
	n_data = data.size();

	if (data_buffer == 0) {
		glGenBuffers(1, &data_buffer);
	}

	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Star) * n_data, &(data[0]), GL_STATIC_DRAW);

	return 1;
}