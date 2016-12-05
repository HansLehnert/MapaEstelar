#pragma once

class Object;

enum MessageType {
	MSG_BASE,
	MSG_INPUT,
	MSG_ACTION,
	MSG_SDL,
	MSG_QUERY
};

struct BaseMessage {
	MessageType type;
	Object* source;
};