#include "KeyboardMouseInputSystem.h"

#include "..\core\message\Message.h"

int KeyboardMouseInputSystem::update() {
	//Arrastre con flechas de teclado
	Message drag_message;
	drag_message.type = MSG_INPUT;
	drag_message.input.event = MSG_INPUT_DRAG;
	drag_message.input.position.x = 0;
	drag_message.input.position.y = 0;

	int drag = 0;
	if (key.right) {
		drag_message.input.position.x = 1;
		drag = 1;
	}
	else if (key.left) {
		drag_message.input.position.x = -1;
		drag = 1;
	}

	if (key.up) {
		drag_message.input.position.y = 1;
		drag = 1;
	}
	else if (key.down) {
		drag_message.input.position.y = -1;
		drag = 1;
	}

	if (drag) {
		drag_message.input.event = MSG_INPUT_DRAG;
		relayMessage(drag_message);
	}

	updateAll();

	return 1;
}

int KeyboardMouseInputSystem::sendMessage(Message msg) {
	if (msg.type = MSG_SDL) {
		switch (msg.sdl.event.type)
		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			switch (msg.sdl.event.key.keysym.sym) {
			case SDLK_RIGHT:
				key.right = msg.sdl.event.type == SDL_KEYDOWN;
				break;
			case SDLK_LEFT:
				key.left = msg.sdl.event.type == SDL_KEYDOWN;
				break;
			case SDLK_UP:
				key.up = msg.sdl.event.type == SDL_KEYDOWN;
				break;
			case SDLK_DOWN:
				key.down = msg.sdl.event.type == SDL_KEYDOWN;
				break;
			/*case SDLK_q:
				key_status[4] = e.type;
				break;
			case SDLK_e:
				key_status[5] = e.type;
				break;*/
			}
			break;
		}
	}

	return 1;
}