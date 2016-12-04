#pragma once

#include <list>

#include "Object.h"
#include "message\Message.h"

class System;

class Component {
public:
	Component(System*, Object*);
	~Component();

	virtual int update() = 0;
	virtual int sendMessage(Message) = 0;

protected:
	System* system;
	Object* object;

	std::list<Component*>::iterator loc;
};