#pragma once

#include "BaseMessage.h"
#include "InputMessage.h"
#include "ActionMessage.h"
#include "SdlMessage.h"

union Message {
	MessageType type;

	BaseMessage   common;
	InputMessage  input;
	ActionMessage action;
	SdlMessage    sdl;
};

