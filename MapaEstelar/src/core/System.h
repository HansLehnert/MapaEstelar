#pragma once

#include <list>

#include "Component.h"
#include "message\Message.h"

class System {
public:
	virtual int update() = 0;
	virtual int sendMessage(Message) = 0;

	int updateAll();

	std::list<Component*> components;
};