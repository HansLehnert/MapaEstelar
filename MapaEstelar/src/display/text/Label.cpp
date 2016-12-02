#include "Label.h"

#include <string>
#include <vector>

Label::Label(RenderSystem* sys, std::string font_name, std::string label_text = " ") :
	GraphicComponent(sys),
	text(label_text),
	color(1), 
	position(0, 0, 0, 1),
	size(0.1, 0.1),
	alignment(Alignment::CENTER),
	whitespace_width(0.8), 
	char_spacing(0.02f) {

	program = GLProgram::getProgram("text");
	font = Font::getFont(font_name);

	uniform_world_mat     = program->uniform["world_matrix"].loc;
	uniform_camera_mat    = program->uniform["camera_matrix"].loc;
	uniform_base_position = program->uniform["base_position"].loc;
	uniform_base_color    = program->uniform["font_color"].loc;
	uniform_scale         = program->uniform["scale"].loc;
	uniform_font_tex      = program->uniform["font_tex"].loc;

	glGenBuffers(1, &mesh.vertex_buffer);
	glGenBuffers(1, &mesh.index_buffer);
	updateDisplay();
}

int Label::render() {
	glUseProgram(program->id);

	glm::mat4 camera_matrix = ((RenderSystem*)system)->camera_matrix;
	glm::vec2 scale;
	scale.x = glm::length(camera_matrix * glm::vec4(1, 0, 0, 0)) * size.x;
	scale.y = glm::length(camera_matrix * glm::vec4(0, 1, 0, 0)) * size.y;

	glUniformMatrix4fv(uniform_world_mat, 1, GL_FALSE, (GLfloat*)&((RenderSystem*)system)->world_matrix);
	glUniformMatrix4fv(uniform_camera_mat, 1, GL_FALSE, (GLfloat*)&camera_matrix);
	glUniform2fv(uniform_scale, 1, (GLfloat*)&scale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->getTextureId());
	glUniform1i(uniform_font_tex, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	glUniform4fv(uniform_base_position, 1, (GLfloat*)&position);
	glUniform4fv(uniform_base_color, 1, (GLfloat*)&color);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(GL_TRIANGLES, mesh.index_length, GL_UNSIGNED_INT, 0);

	return 1;
}

int Label::update() {
	return 1;
}

int Label::setText(std::string new_text) {
	text = new_text;
	return updateDisplay();
}

int Label::setAlignment(Label::Alignment new_alignment) {
	alignment = new_alignment;
	return updateDisplay();
}

int Label::setWhitespaceWidth(float new_width) {
	whitespace_width = new_width;
	return updateDisplay();
}

int Label::updateDisplay() {
	std::vector<glm::vec2> vertex_data;
	std::vector<int> index_data;
	float acc_offset_x = 0;

	const Character* char_data = font->getCharData();

	for (unsigned int i = 0; i < text.length(); i++) {
		float width = char_data[text[i]].width / font->font_size;
		float height = char_data[text[i]].height / font->font_size;
		float offset_y = -char_data[text[i]].offset.y / font->font_size;

		vertex_data.push_back(glm::vec2(acc_offset_x, offset_y));
		vertex_data.push_back(char_data[text[i]].tex_coord[0]);

		vertex_data.push_back(glm::vec2(width + acc_offset_x, offset_y));
		vertex_data.push_back(char_data[text[i]].tex_coord[1]);

		vertex_data.push_back(glm::vec2(acc_offset_x, height + offset_y));
		vertex_data.push_back(char_data[text[i]].tex_coord[2]);

		vertex_data.push_back(glm::vec2(width + acc_offset_x, height + offset_y));
		vertex_data.push_back(char_data[text[i]].tex_coord[3]);

		index_data.push_back(4 * i);
		index_data.push_back(4 * i + 1);
		index_data.push_back(4 * i + 2);
		index_data.push_back(4 * i + 2);
		index_data.push_back(4 * i + 1);
		index_data.push_back(4 * i + 3);

		if (isblank(text[i]))
			acc_offset_x += whitespace_width;
		else
			acc_offset_x += width + char_spacing;
	}

	float offset_correction;
	switch (alignment) {
	case Alignment::CENTER:
		offset_correction = acc_offset_x / 2;
		break;
	case Alignment::RIGHT:
		offset_correction = acc_offset_x;
		break;
	default:
		offset_correction = 0;
		break;
	}

	if (offset_correction != 0) {
		for (unsigned int i = 0; i < text.length(); i++) {
			vertex_data[8 * i].x -= offset_correction;
			vertex_data[8 * i + 2].x -= offset_correction;
			vertex_data[8 * i + 4].x -= offset_correction;
			vertex_data[8 * i + 6].x -= offset_correction;
		}
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