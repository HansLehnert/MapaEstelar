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
private:
	Font font;
	GLProgram* program;
	GLMesh mesh;

	std::string text;

	int updateDisplay();
};