#include "Label.h"

#include <string>
#include <vector>

Label::Label(RenderSystem* sys, std::string font_name, std::string label_text = " ") :
	GraphicComponent(sys),
	font(font_name),
	text(label_text),
	color(1), 
	position(0, 0, 0, 1) {
	program = GLProgram::getProgram("text");

	glGenBuffers(1, &mesh.vertex_buffer);
	glGenBuffers(1, &mesh.index_buffer);
	updateDisplay();
}

int Label::render() {
	glUseProgram(program->id);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font.texture);
	glUniform1i(program->uniform["font_tex"].loc, 0);

	glUniformMatrix4fv(program->uniform["world_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->world_matrix[0][0]));
	glUniformMatrix4fv(program->uniform["camera_matrix"].loc, 1, GL_FALSE, &(((RenderSystem*)system)->camera_matrix[0][0]));
	glUniform4f(program->uniform["base_position"].loc, position.x, position.y, position.z, position.w);
	glUniform4f(program->uniform["font_color"].loc, color.x, color.y, color.z, color.w);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(GL_TRIANGLES, mesh.index_length, GL_UNSIGNED_INT, 0);

	return 1;
}

int Label::update() {
	return 1;
}

int Label::updateDisplay() {
	std::vector<glm::vec2> vertex_data;
	std::vector<int> index_data;
	float acc_offset_x = 0;

	for (unsigned int i = 0; i < text.length(); i++) {
		float width = font.char_data[text[i]].width / font.font_size;
		float height = font.char_data[text[i]].height / font.font_size;
		float offset_y = -font.char_data[text[i]].offset.y / font.font_size;

		vertex_data.push_back(glm::vec2(acc_offset_x, offset_y));
		vertex_data.push_back(font.char_data[text[i]].tex_coord[0]);

		vertex_data.push_back(glm::vec2(width + acc_offset_x, offset_y));
		vertex_data.push_back(font.char_data[text[i]].tex_coord[1]);

		vertex_data.push_back(glm::vec2(acc_offset_x, height + offset_y));
		vertex_data.push_back(font.char_data[text[i]].tex_coord[2]);

		vertex_data.push_back(glm::vec2(width + acc_offset_x, height + offset_y));
		vertex_data.push_back(font.char_data[text[i]].tex_coord[3]);

		index_data.push_back(4 * i);
		index_data.push_back(4 * i + 1);
		index_data.push_back(4 * i + 2);
		index_data.push_back(4 * i + 2);
		index_data.push_back(4 * i + 1);
		index_data.push_back(4 * i + 3);

		if (isblank(text[i]))
			acc_offset_x += 1;
		else
			acc_offset_x += width;
	}

	for (unsigned int i = 0; i < text.length(); i++) {
		vertex_data[8 * i].x -= acc_offset_x / 2;
		vertex_data[8 * i + 2].x -= acc_offset_x / 2;
		vertex_data[8 * i + 4].x -= acc_offset_x / 2;
		vertex_data[8 * i + 6].x -= acc_offset_x / 2;
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		         sizeof(glm::vec2) * vertex_data.size(),
		         &vertex_data[0],
		         GL_STATIC_DRAW);
	mesh.vertex_length = vertex_data.size() / 2;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		         sizeof(int) * index_data.size(),
		         &index_data[0],
		         GL_STATIC_DRAW);
	mesh.index_length = index_data.size();

	return 1;
}