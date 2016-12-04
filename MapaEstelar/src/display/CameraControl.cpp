#include "CameraControl.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

int CameraControl::update() {
	render_system->camera_matrix = camera_matrix;

	return 1;
}


int CameraControl::render() {
	return 1;
}


int CameraControl::sendMessage(Message msg) {
	if (msg.type == MSG_ACTION) {
		switch (msg.action.event) {
		case MSG_ACTION_ROTATE:
			camera_matrix = glm::make_mat4(msg.action.rotation) * camera_matrix;
			break;
		default:
			break;
		}
	}

	return 1;
}