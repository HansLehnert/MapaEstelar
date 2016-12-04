#pragma once

#include "core\Object.h"
#include "input\ManipulationInput.h"
#include "display\CameraControl.h"

class CameraObject : public Object {
public:
	CameraObject(RenderSystem* render_sys, InputSystem* input_sys) :
		Object(new CameraControl(render_sys, this),
			   new ManipulationInput(input_sys, this, InputSystem::Priority::EQUAL))
	{ }
};