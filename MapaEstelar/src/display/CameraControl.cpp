#include "CameraControl.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

CameraControl::CameraControl(RenderSystem* sys, Object* obj) :
	GraphicComponent(sys, obj),
	world_matrix(1),
	zoom_current(1),
	zoom_target(1) {
}


int CameraControl::update() {
	render_system->world_matrix = world_matrix;

	if (zoom_target.x > 5)//Clamp
		zoom_target.x = 5;
	if (zoom_target.y > 5)
		zoom_target.y = 5;

	if (zoom_target.x < 0.5)
		zoom_target.x = 0.5f;
	if (zoom_target.y < 0.5)
		zoom_target.y = 0.5f;

	zoom_current = 0.3f * zoom_target + 0.7f * zoom_current;

	//render_system->camera_matrix = glm::mat4(1.f);
	render_system->camera_matrix[0][0] = zoom_current.x;
	render_system->camera_matrix[1][1] = zoom_current.y;

	return 1;
}


int CameraControl::render() {
	return 1;
}


int CameraControl::sendMessage(Message msg) {
	if (msg.type == MSG_ACTION) {
		switch (msg.action.event) {
		case MSG_ACTION_ROTATE:
			world_matrix = glm::make_mat4(msg.action.rotation) * world_matrix;
			break;

		case MSG_ACTION_SCALE:
			zoom_target *= glm::vec2(msg.action.scale.x, msg.action.scale.y);
			break;

		default:
			break;
		}
	}

	return 1;
}