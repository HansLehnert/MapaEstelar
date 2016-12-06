#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "RenderSystem.h"
#include "GLProgram.h"
#include "GraphicComponent.h"

class CursorMarker : public GraphicComponent {
public:
	CursorMarker(RenderSystem*, Object* = nullptr);

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

private:
	GLMesh mesh;

	GLuint uniform_world_mat;
	GLuint uniform_camera_mat;
	GLuint uniform_base_color;
	GLuint uniform_base_position;
	GLuint uniform_activation;
	GLuint uniform_scale;

	//Variables internas para animación de resaltar
	float activation;
	float activation_target;
	glm::vec4 color_current;
	glm::vec2 position_current;
	glm::vec2 size_current;
};