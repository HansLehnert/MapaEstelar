#pragma once

#include "InputComponent.h"

#include <glm\glm.hpp>

class HighlightInput : public InputComponent {
public:
	HighlightInput(InputSystem* sys, Object* obj, InputSystem::Priority priority) :
		InputComponent(sys, obj, priority)
	{ }

	int update();
	int sendMessage(Message);

private:
	void updateHighlight(float, float);

	glm::vec2 position;
	float radius;

	int idle;
};