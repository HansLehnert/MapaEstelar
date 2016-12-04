#pragma once

class Object;

enum MessageType {
	MSG_BASE,
	MSG_INPUT,
	MSG_ACTION,
	MSG_SDL,
};

struct BaseMessage {
	MessageType type;
	Object* source;
};