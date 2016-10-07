#include "Component.h"

#include "System.h"

Component::Component(System* sys) : system(sys) {
	system->components.push_front(this);
	loc = system->components.begin();
}

Component::~Component() {
	system->components.erase(loc);
}