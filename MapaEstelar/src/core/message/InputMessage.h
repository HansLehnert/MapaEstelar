#pragma once

#include "BaseMessage.h"

#include <glm\glm.hpp>

enum InputEvent {
	MSG_INPUT_MOVE,
	MSG_INPUT_CLICK,
	MSG_INPUT_DRAG,
	MSG_INPUT_PINCH
};

struct InputMessage : public BaseMessage {
	InputEvent event;

	union {
		struct {
			float x;
			float y;
		} position;

		struct {
			float zoom;
			float rotation;
		} pinch;
	};
};