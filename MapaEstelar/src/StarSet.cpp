#include "StarSet.h"

#include <vector>
#include <iostream>

#include <GL\glew.h>

StarSet::StarSet(RenderSystem* sys, Object* obj) :
	GraphicComponent(sys, obj),
	star_buffer(0),
	constellation_buffer(0) {

	program_stars          = GLProgram::getProgram("star");
	program_constellations = GLProgram::getProgram("constellation");
}

int StarSet::update() {
	return 1;
}

int StarSet::sendMessage(Message) {
	return 1;
}

int StarSet::render() {
	if (star_buffer) {
		glUseProgram(program_stars->id);
	
		glUniformMatrix4fv(program_stars->uniform["world_matrix"].loc, 1, GL_FALSE, (GLfloat*)&render_system->world_matrix);
		glUniformMatrix4fv(program_stars->uniform["camera_matrix"].loc, 1, GL_FALSE, (GLfloat*)&render_system->camera_matrix);
		glUniform1f(program_stars->uniform["size_scale"].loc, 1.0f);

		glBindBuffer(GL_ARRAY_BUFFER, star_buffer);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, position));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, color));
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)offsetof(Star, size));

		glDrawArrays(GL_POINTS, 0, star_data.size());
	}

	if (constellation_buffer) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, constellation_buffer);

		//Dibujar estrellas pertenecientes a constelaciones, más grandes
		glUniform1f(program_stars->uniform["size_scale"].loc, 2.0f);
		glDrawElements(GL_POINTS, n_indices, GL_UNSIGNED_INT, 0);

		//Dibujar líneas de constelaciones
		glUseProgram(program_constellations->id);

		glUniformMatrix4fv(program_constellations->uniform["world_matrix"].loc,
			               1,
			               GL_FALSE,
			               (GLfloat*)&render_system->world_matrix);
		glUniformMatrix4fv(program_constellations->uniform["camera_matrix"].loc, 
			               1,
			               GL_FALSE,
			               (GLfloat*)&render_system->camera_matrix);


		glDrawElements(GL_LINES, n_indices, GL_UNSIGNED_INT, 0);
	}

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

	for (auto &constellation : constellation_data) {
		constellation.loc = indices.size();
		indices.insert(indices.end(), constellation.indices.begin(), constellation.indices.end());

		for (auto const &index : constellation.indices) {
			constellation.position += star_data[index].position;
		}
		constellation.position /= constellation.indices.size();
		constellation.position = glm::normalize(constellation.position);
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