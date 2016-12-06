#pragma once

#include "InputSystem.h"
#include "..\findHands.h"

class GestureInputSystem : public InputSystem {
public:
	GestureInputSystem();

	int update();
	int sendMessage(Message);

	handsDetection hands_detection;

	std::thread* cam_thread;

private:
	struct {
		int up = 0;
		int down = 0;
		int left = 0;
		int right = 0;
	} key;

	struct {
		int x = 0;
		int y = 0;
		int left_button = 0;
		int right_button = 0;
	} mouse;
};
