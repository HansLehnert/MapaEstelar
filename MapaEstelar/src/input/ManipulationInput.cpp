#include "ManipulationInput.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\display\GraphicComponent.h"

int ManipulationInput::update() {
	/*if (offset.x != 0 || offset.y != 0) {
		float offset_len = glm::length(offset);
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1), offset_len * 0.1f, glm::vec3(-offset.y, offset.x, 0));

		Message msg;
		msg.type = MSG_ACTION;
		msg.action.event = MSG_ACTION_ROTATE;
		memcpy(msg.action.rotation, &rotation_matrix, sizeof(rotation_matrix));

		object->graphic_component->sendMessage(msg);

		if (offset_len < 0.1)
			offset = glm::vec2(0);
		else
			offset *= 0.9;
	}*/
	
	return 1;
}


int ManipulationInput::sendMessage(Message msg) {
	Message new_msg;

	if (msg.type == MSG_INPUT) {
		switch (msg.input.event) {
		case MSG_INPUT_DRAG:
			/*offset.x += msg.input.position.x;
			offset.y += msg.input.position.y;*/
			new_msg.type = MSG_ACTION;
			new_msg.action.event = MSG_ACTION_MOVE;
			new_msg.action.position.x = -msg.input.position.x;
			new_msg.action.position.y = -msg.input.position.y;
			object->graphic_component->sendMessage(new_msg);
			break;

		case MSG_INPUT_PINCH:
			new_msg.type = MSG_ACTION;
			new_msg.action.event = MSG_ACTION_SCALE;
			new_msg.action.scale.x = (8 + msg.input.pinch.zoom) / 8;
			new_msg.action.scale.y = new_msg.action.scale.x;
			object->graphic_component->sendMessage(new_msg);
			break;

		default:
			break;
		}
	}

	return 1;
}