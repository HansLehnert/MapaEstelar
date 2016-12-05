#pragma once

#include "BaseMessage.h"
#include "InputMessage.h"
#include "ActionMessage.h"
#include "QueryMessage.h"
#include "SdlMessage.h"

union Message {
	MessageType type;

	BaseMessage   common;
	InputMessage  input;
	ActionMessage action;
	QueryMessage  query;
	SdlMessage    sdl;
};

