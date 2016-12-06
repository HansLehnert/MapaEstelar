#include "CursorMarker.h"

#include <vector>

CursorMarker::CursorMarker(RenderSystem* sys, Object* obj) :
	GraphicComponent(sys, obj) {

	std::vector<float> vertex_data;

	int N_VERTEX = 6;

	for (int i = 0; i < N_VERTEX + 1; i++) {
		vertex_data.push_back(0.1 * cos(2 * 3.1415 * i / N_VERTEX));
		vertex_data.push_back(0.1 * sin(2 * 3.1415 * i / N_VERTEX));
		vertex_data.push_back(0.f);
		vertex_data.push_back(1.f);
		vertex_data.push_back(float(i) / (N_VERTEX + 1));
		vertex_data.push_back(0.08 * cos(2 * 3.1415 * i / N_VERTEX));
		vertex_data.push_back(0.08 * sin(2 * 3.1415 * i / N_VERTEX));
		vertex_data.push_back(0.f);
		vertex_data.push_back(1.f);
		vertex_data.push_back(float(i) / (N_VERTEX + 1));
	}

	glGenBuffers(1, &mesh.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), &vertex_data[0], GL_STATIC_DRAW);
	mesh.vertex_length = vertex_data.size() / 5;

	program = GLProgram::getProgram("cursor");

	uniform_scale =         program->uniform["scale"].loc;
	uniform_base_color =    program->uniform["base_color"].loc;
	uniform_base_position = program->uniform["base_position"].loc;
	uniform_activation =    program->uniform["activation"].loc;

	size_current = glm::vec2(0.6);
	color_current = glm::vec4(0, 1, 0.9, 0.8);
	position_current = glm::vec2(0);
	activation = 1;
}


int CursorMarker::render() {
	glUseProgram(program->id);

	glm::vec2 scale = render_system->getAspectRatio() * size_current;

	//scale.x = glm::length(render_system->camera_matrix * glm::vec4(1, 0, 0, 0)) * size_current.x;
	//scale.y = glm::length(render_system->camera_matrix * glm::vec4(0, 1, 0, 0)) * size_current.y;

	glDisableVertexAttribArray(1);

	glUniform4fv(uniform_base_color, 1, (GLfloat*)&color_current);
	glUniform2fv(uniform_base_position, 1, (GLfloat*)&position_current);
	glUniform2fv(uniform_scale, 1, (GLfloat*)&scale);
	glUniform1f(uniform_activation, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLfloat*)(4 * sizeof(float)));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh.vertex_length);

	glEnableVertexAttribArray(1);
	
	return 1;
}


int CursorMarker::update() {
	return 1;
}


int CursorMarker::sendMessage(Message msg) {
	switch (msg.type) {
	case MSG_ACTION:
		if (msg.input.event == MSG_ACTION_MOVE) {
			position_current.x = msg.action.position.x;
			position_current.y = msg.action.position.y;
		}
		break;
	}

	return 1;
}