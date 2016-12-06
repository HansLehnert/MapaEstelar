#include "CursorInput.h"

#include "..\core\Object.h"
#include "..\display\GraphicComponent.h"

int CursorInput::update() {
	return 1;
}

int CursorInput::sendMessage(Message msg) {
	Message new_msg;

	switch (msg.type) {
	case MSG_INPUT:
		switch (msg.input.event) {
		case MSG_INPUT_MOVE:
			new_msg.type = MSG_ACTION;
			new_msg.action.event = MSG_ACTION_MOVE;
			new_msg.action.position.x = msg.input.position.x;
			new_msg.action.position.y = msg.input.position.y;
			object->graphic_component->sendMessage(new_msg);
			break;

		case MSG_INPUT_CLICK:
			object->graphic_component->sendMessage(msg);
			break;
		}
		break;
	}
	return 1;
}