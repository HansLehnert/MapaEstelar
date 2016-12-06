#pragma once

#include "InputComponent.h"

#include <glm\glm.hpp>

class CursorInput : public InputComponent {
public:
	CursorInput(InputSystem* sys, Object* obj, InputSystem::Priority priority) :
		InputComponent(sys, obj, priority)
	{ }

	int update();
	int sendMessage(Message);

private:
	int idle;
};