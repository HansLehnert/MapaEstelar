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
	Message new_msg;

	if (msg.type = MSG_SDL) {
		switch (msg.sdl.event.type) {
		//Guardar cambio de estado en las teclas
		case SDL_KEYDOWN:
		case SDL_KEYUP:
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

		//Zoom con rueda de mouse
		case SDL_MOUSEWHEEL:
			new_msg.type = MSG_INPUT;
			new_msg.input.event = MSG_INPUT_PINCH;
			new_msg.input.pinch.zoom = msg.sdl.event.wheel.y;

			if (new_msg.input.pinch.zoom != 0)
				relayMessage(new_msg);
			break;

		//Estado de botones de mouse
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			switch (msg.sdl.event.button.button) {
			case SDL_BUTTON_LEFT:
				mouse.left_button = msg.sdl.event.button.state == SDL_PRESSED;
				if (mouse.left_button) {
					msg.type = MSG_INPUT;
					msg.input.event = MSG_INPUT_CLICK;
					new_msg.input.position.x = msg.sdl.event.motion.x / 400.f - 1; //Transformacion a coordenadas normalizadas.
					new_msg.input.position.y = -msg.sdl.event.motion.y / 225.f + 1; //Implementación horrible. Arreglar.
					relayMessage(new_msg);
				}
				break;
			case SDL_BUTTON_RIGHT:
				mouse.right_button = msg.sdl.event.button.state == SDL_PRESSED;
				break;
			}
			break;

		//Arrastre por mouse
		case SDL_MOUSEMOTION:
			if (mouse.right_button && (msg.sdl.event.motion.xrel != 0 || msg.sdl.event.motion.xrel != 0)) {
				new_msg.type = MSG_INPUT;
				new_msg.input.event = MSG_INPUT_DRAG;
				new_msg.input.position.x = msg.sdl.event.motion.xrel * 0.2;
				new_msg.input.position.y = -msg.sdl.event.motion.yrel * 0.2;
				relayMessage(new_msg);
			}

			//Actualización de posición
			mouse.x = msg.sdl.event.motion.x;
			mouse.y = msg.sdl.event.motion.x;

			new_msg.type = MSG_INPUT;
			new_msg.input.event = MSG_INPUT_MOVE;
			new_msg.input.position.x = msg.sdl.event.motion.x / 400.f - 1; //Transformacion a coordenadas normalizadas.
			new_msg.input.position.y = -msg.sdl.event.motion.y / 225.f + 1; //Implementación horrible. Arreglar.
			relayMessage(new_msg);
			break;
		}
	}

	return 1;
}