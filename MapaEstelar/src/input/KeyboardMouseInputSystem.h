#pragma once

#include "InputSystem.h"

class KeyboardMouseInputSystem : public InputSystem {
public:
	int update();
	int sendMessage(Message);

private:
	struct {
		int up = 0;
		int down = 0;
		int left = 0;
		int right = 0;
	} key;
};