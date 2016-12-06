#include "GestureInputSystem.h"

#include <thread>

#include "..\core\message\Message.h"
#include "..\findHands.h"

GestureInputSystem::GestureInputSystem() {
	cam_thread = new std::thread(handsDetection::init, &hands_detection);
}

int GestureInputSystem::update() {
	Message msg;
	msg.type = MSG_INPUT;

	if (hands_detection.gesture_flag == 1) {
		msg.input.event = MSG_INPUT_DRAG;
		msg.input.position.x = hands_detection.dx * 0.1;
		msg.input.position.y = hands_detection.dy * 0.1;
		relayMessage(msg);

		msg.input.event = MSG_INPUT_MOVE;
		msg.input.position.x = -(hands_detection.end_point.x / 320.0 - 1);
		msg.input.position.y = -(hands_detection.end_point.y / 240.0 - 1);
		relayMessage(msg);
	}

	if (hands_detection.gesture_flag == 2) {
		msg.input.event = MSG_INPUT_PINCH;
		msg.input.pinch.zoom = hands_detection.zoom_ratio;
		relayMessage(msg);
	}

	if (hands_detection.gesture_flag == 3) {
		msg.input.event = MSG_INPUT_CLICK;
		msg.input.position.x = -(hands_detection.pointing_place.x / 320.0 - 1);
		msg.input.position.y = -(hands_detection.pointing_place.y / 240.0 - 1);
		relayMessage(msg);

		msg.input.event = MSG_INPUT_MOVE;
		msg.input.position.x = -(hands_detection.pointing_place.x / 320.0 - 1);
		msg.input.position.y = -(hands_detection.pointing_place.y / 240.0 - 1);
		relayMessage(msg);
	}

	updateAll();

	return 1;
}

int GestureInputSystem::sendMessage(Message msg) {
	
	return 1;
}