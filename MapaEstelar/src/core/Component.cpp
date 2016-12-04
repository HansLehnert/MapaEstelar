#include "Component.h"

#include "System.h"

Component::Component(System* sys, Object* obj) : system(sys), object(obj) {
	system->components.push_front(this);
	loc = system->components.begin();
}

Component::~Component() {
	system->components.erase(loc);
}