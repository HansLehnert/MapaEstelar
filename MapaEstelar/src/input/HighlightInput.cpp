#include "HighlightInput.h"

#include "..\core\Object.h"
#include "..\display\GraphicComponent.h"

int HighlightInput::update() {
	idle = 1;

	return 1;
}

int HighlightInput::sendMessage(Message msg) {
	switch (msg.type) {
	case MSG_INPUT:
		if (msg.input.event == MSG_INPUT_MOVE && idle) {
			updateHighlight(msg.input.position.x, msg.input.position.y);
			idle = 0;
		}
		break;

	case MSG_QUERY:
		if (msg.query.type == MSG_QUERY_RESPONSE) {
			switch (msg.query.value) {
			case MSG_QUERY_LOCATION:
				position.x = msg.query.position.x;
				position.y = msg.query.position.y;
				radius = msg.query.position.r;
			}
		}
	}

	return 1;
}

void HighlightInput::updateHighlight(float x, float y) {
	//Obtener posición
	Message msg;
	msg.type = MSG_QUERY;
	msg.query.source = this;
	msg.query.type = MSG_QUERY_REQUEST;
	msg.query.value = MSG_QUERY_LOCATION;
	object->graphic_component->sendMessage(msg);

	//Comparar posición de mouse y objeto
	float distance = (x - position.x) * (x - position.x) + (y - position.y) * (y - position.y);
	float activation = 0;
	if (distance < radius)
		activation = 1 - distance / radius;

	//Enviar mensaje de actualización
	msg.type = MSG_ACTION;
	msg.action.event = MSG_ACTION_HIGHLIGHT;
	msg.action.highlight = activation;
	object->graphic_component->sendMessage(msg);
}