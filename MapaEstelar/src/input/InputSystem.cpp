#include "InputSystem.h"

#include "InputComponent.h"

InputSystem::InputSystem() {
	priority_stack.push_back(InputList());
}


int InputSystem::update() {
	return 1;
}


int InputSystem::sendMessage(Message) {
	return 1;
}


int InputSystem::subscribe(InputComponent* component, Priority priority) {
	switch (priority) {
	case Priority::TOP:
		priority_stack.push_back(InputList()); //Sin break!
	case Priority::EQUAL:
		priority_stack.back().push_back(component);
		break;
	case Priority::FREE:
		priority_free.push_back(component);
		break;
	default:
		return 0;
		break;
	}

	return 1;
}


int InputSystem::relayMessage(Message message) {
	for (auto component : priority_free) {
		component->sendMessage(message);
	}

	for (auto component : priority_stack.back()) {
		component->sendMessage(message);
	}

	return 1;
}