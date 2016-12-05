#pragma once

#include "BaseMessage.h"

#include <glm\glm.hpp>

enum ActionEvent {
	MSG_ACTION_MOVE,
	MSG_ACTION_ROTATE,
	MSG_ACTION_SCALE,
	MSG_ACTION_COLOR,
	MSG_ACTION_HIGHLIGHT
};

struct ActionMessage : public BaseMessage {
	ActionEvent event;

	union {
		struct {
			float x;
			float y;
			float z;
		} position;

		float rotation[16];
		
		struct {
			float x;
			float y;
		} scale;

		struct {
			float r;
			float g;
			float b;
			float a;
		} color;

		float highlight;
	};
};