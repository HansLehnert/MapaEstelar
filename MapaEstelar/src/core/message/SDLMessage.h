#pragma once

#include <SDL_events.h>

#include "BaseMessage.h"

struct SdlMessage : public BaseMessage {
	SDL_Event event;
};