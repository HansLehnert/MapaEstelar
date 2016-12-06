#include "CameraControl.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

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

	//Rotar camara
	if (offset.x != 0 || offset.y != 0) {
		float offset_len = glm::length(offset);

		glm::mat3 pose = render_system->getPose();

		glm::vec3 right_vec = pose * glm::vec3(1, 0, 0);
		glm::vec3 up_vec = pose * glm::vec3(0, 1, 0);

		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1), offset_len * 0.1f, -right_vec * offset.y + up_vec * offset.x);

		/*Message msg;
		msg.type = MSG_ACTION;
		msg.action.event = MSG_ACTION_ROTATE;
		memcpy(msg.action.rotation, &rotation_matrix, sizeof(rotation_matrix));*/

		//object->graphic_component->sendMessage(msg);

		if (offset_len < 0.1)
			offset = glm::vec2(0);
		else
			offset *= 0.9;
		
		world_matrix = rotation_matrix * world_matrix;
	}

	return 1;
}


int CameraControl::render() {
	return 1;
}


int CameraControl::sendMessage(Message msg) {
	if (msg.type == MSG_ACTION) {
		switch (msg.action.event) {
		case MSG_ACTION_MOVE:
			//world_matrix = glm::make_mat4(msg.action.rotation) * world_matrix;
			offset.x += msg.action.position.x;
			offset.y += msg.action.position.y;
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