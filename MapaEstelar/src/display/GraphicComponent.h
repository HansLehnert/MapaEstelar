#pragma once

#include "RenderSystem.h"
#include "../core/Component.h"

class GraphicComponent : public Component {
public:
	GraphicComponent(RenderSystem* sys) : Component(sys) { };
	virtual int update() = 0;
};