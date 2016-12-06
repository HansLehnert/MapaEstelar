#pragma once

#include "core\Object.h"
#include "input\CursorInput.h"
#include "display\CursorMarker.h"

class CursorObject : public Object {
public:
	CursorObject(RenderSystem* render_sys, InputSystem* input_sys) :
		Object(new CursorMarker(render_sys, this),
			new CursorInput(input_sys, this, InputSystem::Priority::FREE))
	{ }
};