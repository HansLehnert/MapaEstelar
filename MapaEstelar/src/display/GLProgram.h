#pragma once

#include <map>
#include <string>

#include <GL\glew.h>

class GLProgram {
public:
	GLuint id;
	GLuint world_loc;
	GLuint camera_loc;
	GLuint model_loc;

	static GLProgram* getProgram(std::string);
private:
	static std::map<std::string, GLProgram> program_cache;
	static GLuint loadShader(std::string, GLuint);
};

