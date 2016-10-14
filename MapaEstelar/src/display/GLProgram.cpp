#include "GLProgram.h"

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL\glew.h>

const char* SHADER_PATH = "rsrc/shader/";

std::map<std::string, GLProgram> GLProgram::program_cache;

GLProgram* GLProgram::getProgram(std::string name) {
	if (program_cache.find(name) == program_cache.end()) {
		GLProgram new_program;
		
		new_program.id = glCreateProgram();

		GLuint vertex_shader = loadShader(SHADER_PATH + name + "_vert.glsl", GL_VERTEX_SHADER);
		GLuint fragment_shader = loadShader(SHADER_PATH + name + "_frag.glsl", GL_FRAGMENT_SHADER);

		if (vertex_shader)
			glAttachShader(new_program.id, vertex_shader);
		if (fragment_shader)
			glAttachShader(new_program.id, fragment_shader);

		glLinkProgram(new_program.id);

		if (vertex_shader) {
			glDetachShader(new_program.id, vertex_shader);
			glDeleteShader(fragment_shader);
		}

		if (vertex_shader) {
			glDetachShader(new_program.id, fragment_shader);
			glDeleteShader(fragment_shader);
		}

		//Get uniform locations
		GLint uniform_count;
		glGetProgramiv(new_program.id, GL_ACTIVE_UNIFORMS, &uniform_count);
		for (int i = 0; i < uniform_count; i++) {
			Uniform new_uniform;
			GLsizei length;
			GLchar uniform_name[16];
	
			glGetActiveUniform(new_program.id, i, 16, &length, &(new_uniform.size), &(new_uniform.type), uniform_name);
			new_uniform.loc = glGetUniformLocation(new_program.id, uniform_name);

			new_program.uniform[uniform_name] = new_uniform;
		}

		program_cache[name] = new_program;
	}
	return &(program_cache[name]);
}

GLuint GLProgram::loadShader(std::string path, GLuint type) {
	GLint success;
	GLuint shader;

	//Leer archivo completo
	std::ifstream shader_file(path);
	std::stringstream file_buffer;
	if (!shader_file.is_open()) {
		std::cout << "No se pudo abrir el archivo " << path << std::endl;
		return 0;
	}

	file_buffer << shader_file.rdbuf();
	std::string file_content = file_buffer.str();
	const char* file_content_c = file_content.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &file_content_c, NULL);
	glCompileShader(shader);

	//Revisar fallo en compilación
	//Imprimir errores en tal caso
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint log_length;
		GLchar* log_content;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		log_content = new GLchar[log_length];
		glGetShaderInfoLog(shader, log_length, NULL, log_content);
		std::cout << log_content << std::endl;
		return 0;
	}

	return shader;
}