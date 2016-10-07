#pragma once

#include "BaseMessage.h"

union Message {
	int type;
	BaseMessage common;
};

