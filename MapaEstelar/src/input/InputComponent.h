#pragma once

#include "../core/Component.h"
#include "InputSystem.h"

class InputComponent : public Component {
public:
	InputComponent(InputSystem*, Object*, InputSystem::Priority);
	virtual int update() = 0;
	virtual int sendMessage(Message) = 0;

protected:
	InputSystem* input_system;
};