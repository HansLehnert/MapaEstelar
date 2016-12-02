#pragma once

#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Font.h"
#include "..\RenderSystem.h"
#include "..\GLProgram.h"
#include "..\GraphicComponent.h"

class Label : public GraphicComponent {
public:
	Label(RenderSystem*, std::string, std::string);

	int render();
	int update();

	glm::vec4 color;
	glm::vec4 position;
	glm::vec2 size;

	enum class Alignment {
		LEFT,
		CENTER,
		RIGHT
	};

	int setText(std::string);
	int setAlignment(Alignment);
	int setWhitespaceWidth(float);
private:
	Font* font;
	GLMesh mesh;

	GLuint uniform_world_mat;
	GLuint uniform_camera_mat;
	GLuint uniform_base_color;
	GLuint uniform_base_position;
	GLuint uniform_scale;
	GLuint uniform_font_tex;

	//Opciones de texto
	std::string text;
	Alignment alignment;
	float char_spacing;
	float whitespace_width;

	int updateDisplay();
};