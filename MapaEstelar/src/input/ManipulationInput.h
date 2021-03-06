#pragma once

#include "InputComponent.h"

#include <glm\glm.hpp>

class ManipulationInput : public InputComponent {
public:
	ManipulationInput(InputSystem* sys, Object* obj, InputSystem::Priority priority) :
		InputComponent(sys, obj, priority),
		offset(0)
	{ }

	int update();
	int sendMessage(Message);

private:
	glm::vec2 offset;
};