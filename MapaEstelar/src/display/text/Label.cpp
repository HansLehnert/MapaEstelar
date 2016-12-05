#include "Label.h"

#include <string>
#include <vector>

Label::Label(RenderSystem* sys, Object* obj, std::string font_name, std::string label_text) :
	GraphicComponent(sys, obj),

	text(label_text),
	activation(0),
	activation_target(0),
	/*color_inactive(1),
	color_active(1),
	position_inactive(0, 0, 0, 1),
	position_active(0, 0, 0, 1),
	size_inactive(0.1, 0.1),
	size_active(0.1, 0.1),*/

	alignment(Alignment::CENTER),
	whitespace_width(0.8f), 
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

	glm::vec2 scale;

	scale.x = glm::length(render_system->camera_matrix * glm::vec4(1, 0, 0, 0)) * size_current.x;
	scale.y = glm::length(render_system->camera_matrix * glm::vec4(0, 1, 0, 0)) * size_current.y;

	glUniformMatrix4fv(uniform_world_mat, 1, GL_FALSE, (GLfloat*)&render_system->world_matrix);
	glUniformMatrix4fv(uniform_camera_mat, 1, GL_FALSE, (GLfloat*)&render_system->camera_matrix);
	glUniform2fv(uniform_scale, 1, (GLfloat*)&scale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->getTextureId());
	glUniform1i(uniform_font_tex, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	glUniform4fv(uniform_base_position, 1, (GLfloat*)&position_current);
	glUniform4fv(uniform_base_color, 1, (GLfloat*)&color_current);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(GL_TRIANGLES, mesh.index_length, GL_UNSIGNED_INT, 0);

	return 1;
}


int Label::update() {
	//Actualización de posicion, color, tamaño; para resaltar
	activation = 0.3 * activation_target + 0.7 * activation;

	size_current = size_active * activation + size_inactive * (1 - activation);
	color_current = color_active * activation + color_inactive * (1 - activation);
	position_current = position_active * activation + position_inactive * (1 - activation);

	return 1;
}


int Label::sendMessage(Message msg) {
	Message new_msg;

	switch (msg.type) {
	case MSG_QUERY:
		if (msg.query.type == MSG_QUERY_REQUEST && msg.query.source != nullptr) {
			switch (msg.query.value) {
			case MSG_QUERY_LOCATION:
				glm::vec4 proyection = render_system->camera_matrix
					//* render_system->getCameraMatrix()
					* render_system->world_matrix
					* position_current;

				new_msg.type = MSG_QUERY;
				new_msg.query.type = MSG_QUERY_RESPONSE;
				new_msg.query.value = MSG_QUERY_LOCATION;
				new_msg.query.position.x = proyection.x / proyection.w;
				new_msg.query.position.y = proyection.y / proyection.w;
				new_msg.query.position.r = 0.2;

				msg.common.source->sendMessage(new_msg);
			}
		}

	case MSG_ACTION:
		if (msg.action.event == MSG_ACTION_HIGHLIGHT) {
			activation_target = msg.action.highlight;
		}
	}
	
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