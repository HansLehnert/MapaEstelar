#pragma once

class Entity;

struct BaseMessage {
	int type;
	Entity* source;
};