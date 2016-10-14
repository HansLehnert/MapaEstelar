#pragma once

#include <map>
#include <string>

#include <GL\glew.h>

class GLProgram {
public:
	GLuint id;

	struct Uniform {
		GLenum type;
		GLuint loc;
		GLint size;
	};
	std::map<std::string, Uniform> uniform;

	static GLProgram* getProgram(std::string);
private:
	static std::map<std::string, GLProgram> program_cache;
	static GLuint loadShader(std::string, GLuint);

	
};

