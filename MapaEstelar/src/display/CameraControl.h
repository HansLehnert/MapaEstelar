#pragma once

#include "GraphicComponent.h"

#include <glm\glm.hpp>

class CameraControl : public GraphicComponent {
public:
	CameraControl(RenderSystem* sys, Object* obj) :
		GraphicComponent(sys, obj) { }

	int update();
	int render();
	int sendMessage(Message);

private:
	glm::mat4 camera_matrix;
};