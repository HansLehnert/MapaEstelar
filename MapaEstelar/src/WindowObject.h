#pragma once

#include "core\Object.h"
#include "input\WindowInput.h"
#include "display\text\Textbox.h"

class WindowObject : public Object {
public:
	WindowObject(RenderSystem* render_sys, InputSystem* input_sys) :
		Object(new Textbox(render_sys, this, "rsrc/font/MuseoSans-500.otf", "hola"),
			new WindowInput(input_sys, this, InputSystem::Priority::FREE))
	{ }
};