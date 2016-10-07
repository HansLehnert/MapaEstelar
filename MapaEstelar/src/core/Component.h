#pragma once

#include <list>

class System;

class Component {
public:
	Component(System* sys);
	~Component();

	virtual int update() = 0;

protected:
	System* system;
	std::list<Component*>::iterator loc;
};