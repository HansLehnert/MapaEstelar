#pragma once

#include "GraphicComponent.h"

#include <glm\glm.hpp>

class CameraControl : public GraphicComponent {
public:
	CameraControl(RenderSystem*, Object*);

	int update();
	int render();
	int sendMessage(Message);

private:
	glm::mat4 world_matrix;

	glm::vec2 zoom_current;
	glm::vec2 zoom_target;
};