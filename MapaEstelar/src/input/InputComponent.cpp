#include "InputComponent.h"

InputComponent::InputComponent(InputSystem* sys, Object* obj, InputSystem::Priority priority) :
	Component(sys, obj),
	input_system(sys) {

	input_system->subscribe(this, priority);
}
