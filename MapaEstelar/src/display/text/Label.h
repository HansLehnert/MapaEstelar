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
	Label(RenderSystem*, Object*, std::string, std::string);

	int render();
	int update();
	int sendMessage(Message);

	//Configuración de texto
	//2 estados: activo inactivo
	glm::vec4 color_inactive;
	glm::vec4 color_active;

	glm::vec4 position_inactive;
	glm::vec4 position_active;

	glm::vec2 size_inactive;
	glm::vec2 size_active;

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
	std::string text;       //Texto a mostrar
	Alignment alignment;    //Alineamiento del texto
	float char_spacing;     //Espacio entre caracteres
	float whitespace_width; //Ancho de espacios (caracteres blancos)

	//Variables internas para animación de resaltar
	float activation;
	float activation_target;
	glm::vec4 color_current;
	glm::vec4 position_current;
	glm::vec2 size_current;

	int updateDisplay();
};