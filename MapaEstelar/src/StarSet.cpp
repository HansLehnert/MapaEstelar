#include "StarSet.h"

#include <vector>
#include <iostream>

#include <GL\glew.h>

StarSet::StarSet(RenderSystem* sys) :
	GraphicComponent(sys),
	star_buffer(0),
	constellation_buffer(0) {
	program = GLProgram::getProgram("star");
}

int StarSet::update(){
	return 1;
}

int StarSet::render() {
	glUseProgram(program->id);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	
	glUniformMatrix4fv(program->uniform["world_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->world_matrix[0][0]));
	glUniformMatrix4fv(program->uniform["camera_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->camera_matrix[0][0]));

	if (star_buffer) {
		glBindBuffer(GL_ARRAY_BUFFER, star_buffer);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, position));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, color));
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, size));

		glDrawArrays(GL_POINTS, 0, star_data.size());
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, constellation_buffer);

		glDrawElements(GL_POINTS, n_indices, GL_UNSIGNED_INT, 0);*/
	}

	if (constellation_buffer) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, constellation_buffer);

		glDrawElements(GL_LINES, n_indices, GL_UNSIGNED_INT, 0);
	}

	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

	return 1;
}

int StarSet::loadStars() {
	if (star_data.size() == 0) {
		return 0;
	}

	if (star_buffer == 0) {
		glGenBuffers(1, &star_buffer);
	}

	glBindBuffer(GL_ARRAY_BUFFER, star_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Star) * star_data.size(), &star_data[0], GL_STATIC_DRAW);

	return 1;
}

int StarSet::loadConstellations() {
	std::vector<int> indices;

	for (auto constellation : constellation_data) {
		constellation.loc = indices.size();
		indices.insert(indices.end(), constellation.indices.begin(), constellation.indices.end());
	}

	n_indices = indices.size();

	if (n_indices == 0) {
		return 0;
	}

	if (constellation_buffer == 0) {
		glGenBuffers(1, &constellation_buffer);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, constellation_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * n_indices, &indices[0], GL_STATIC_DRAW);

	return 1;
}