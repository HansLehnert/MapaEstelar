#pragma once

#include <list>

#include "Component.h"

class System {
public:
	virtual int update() = 0;
	//void sendMessage(Message);

	std::list<Component*> components;
};