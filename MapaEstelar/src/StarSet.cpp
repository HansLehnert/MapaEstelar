#include "StarSet.h"

#include <vector>
#include <iostream>

#include <GL\glew.h>


const char* VERTEX_SHADER = R"glsl(
#version 330

layout (location = 0) in vec4 position;

uniform mat4 camera;
uniform mat4 world;

void main() {
	gl_Position = camera * world * position;
	gl_PointSize = 4.0;
}

)glsl";

const char* FRAGMENT_SHADER = R"glsl(
#version 330

out vec4 frag_color;

void main() {
	frag_color = vec4(1.0, 1.0, 0.0, 1.0);
}

)glsl";

StarSet::StarSet(RenderSystem* sys) :
	GraphicComponent(sys),
	data_buffer(0),
	program(0) {

}

int StarSet::update() {
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUseProgram(program);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Star), 0);

	GLuint world_loc = glGetUniformLocation(program, "world");
	GLuint camera_loc = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(world_loc, 1, GL_FALSE, &(((RenderSystem*)system)->world_matrix[0][0]));
	glUniformMatrix4fv(camera_loc, 1, GL_FALSE, &(((RenderSystem*)system)->camera_matrix[0][0]));

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

	//Mover esto de aqui. Esta horrible.
	if (program == 0) {
		program = glCreateProgram();

		GLint success;
		GLuint vertex_shader;
		GLuint fragment_shader;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &VERTEX_SHADER, NULL);
		glCompileShader(vertex_shader);

		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint log_length;
			GLchar* log_content;

			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
			log_content = new GLchar[log_length];
			glGetShaderInfoLog(vertex_shader, log_length, NULL, log_content);
			std::cout << log_content << std::endl;
		}
		else {
			glAttachShader(program, vertex_shader);
		}

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &FRAGMENT_SHADER, NULL);
		glCompileShader(fragment_shader);

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint log_length;
			GLchar* log_content;

			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
			log_content = new GLchar[log_length];
			glGetShaderInfoLog(fragment_shader, log_length, NULL, log_content);
			std::cout << log_content << std::endl;
		}
		else {
			glAttachShader(program, fragment_shader);
		}

		glLinkProgram(program);

		/*glDetachShader(program, vertex_shader);
		glDetachShader(program, fragment_shader);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);*/
	}

	return 1;
}