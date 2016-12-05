#pragma once

class Component;

enum MessageType {
	MSG_BASE,
	MSG_INPUT,
	MSG_ACTION,
	MSG_SDL,
	MSG_QUERY
};

struct BaseMessage {
	MessageType type;
	Component* source;
};