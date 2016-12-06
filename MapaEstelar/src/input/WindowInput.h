#pragma once

#include "InputComponent.h"

#include <glm\glm.hpp>

class WindowInput : public InputComponent {
public:
	WindowInput(InputSystem* sys, Object* obj, InputSystem::Priority priority) :
		InputComponent(sys, obj, priority),
		offset(0)
	{ }

	int update();
	int sendMessage(Message);

private:
	glm::vec2 offset;
};