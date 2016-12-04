#pragma once

#include "RenderSystem.h"
#include "GLProgram.h"
#include "../core/Component.h"

class GraphicComponent : public Component {
public:
	GraphicComponent(RenderSystem* sys, Object* obj = nullptr) : Component(sys, obj), render_system(sys) { };
	virtual int update() = 0;
	virtual int render() = 0;
	virtual int sendMessage(Message) = 0;
	
protected:
	RenderSystem* render_system;
	GLProgram* program;
};