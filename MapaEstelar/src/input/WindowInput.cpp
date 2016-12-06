#include "WindowInput.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\display\GraphicComponent.h"

int WindowInput::update() {
	if (offset.x != 0 || offset.y != 0) {
		Message msg;
		msg.type = MSG_ACTION;
		msg.action.event = MSG_ACTION_MOVE;
		msg.action.position.x = offset.x / 40;
		msg.action.position.y = offset.y / 40;
		object->graphic_component->sendMessage(msg);

		if (glm::length(offset) > 20) {
			msg.type = MSG_ACTION;
			msg.action.event = MSG_ACTION_HIGHLIGHT;
			msg.action.highlight = 0;
			object->graphic_component->sendMessage(msg);
		}

		offset *= 0.9;
	}

	return 1;
}


int WindowInput::sendMessage(Message msg) {
	Message new_msg;

	if (msg.type == MSG_INPUT) {
		switch (msg.input.event) {
		case MSG_INPUT_DRAG:
			offset.x += msg.input.position.x;
			offset.y += msg.input.position.y;
			/*new_msg.type = MSG_ACTION;
			new_msg.action.event = MSG_ACTION_MOVE;
			new_msg.action.position.x = msg.input.position.x;
			new_msg.action.position.y = msg.input.position.y;
			object->graphic_component->sendMessage(new_msg);*/
			break;

		default:
			break;
		}
	}

	return 1;
}