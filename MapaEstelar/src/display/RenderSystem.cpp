#include "RenderSystem.h"

#include <iostream>
#include <list>

#include <SDL.h>
#include <osvr\ClientKit\Context.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

RenderSystem::RenderSystem() :
	camera_matrix(1),
	world_matrix(1) {

}

RenderSystem::~RenderSystem() {
	if (display.enabled) {
		if (display.context)
			SDL_GL_DeleteContext(display.context);
		
		if (display.handle != nullptr)
			SDL_DestroyWindow(display.handle);
	}

	if (window.enabled) {
		if (window.context)
			SDL_GL_DeleteContext(window.context);

		if (window.handle != nullptr)
			SDL_DestroyWindow(window.handle);
	}

	SDL_Quit();
}


int RenderSystem::init() {
	window.enabled = 0;
	display.enabled = 1;

	glewExperimental = GL_TRUE;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to init SDL." << std::endl;
		return 0;
	}
	SDL_GL_SetSwapInterval(1); //Enable v-sync

	osvr_context = new osvr::clientkit::ClientContext("MapaEstelar");
	if (!osvr_context->checkStatus()) {
		std::cout << "Failed to start OSVR context." << std::endl;
		std::cout << "Server may not be running." << std::endl;
		display.enabled = 0;
	}

	if (display.enabled) {
		display.config = new osvr::clientkit::DisplayConfig(*osvr_context);
		if (display.config->valid()) {
			while (!display.config->checkStartup()) {
				osvr_context->update();
			}

			//Busqueda del display por nombre
			int n_display = SDL_GetNumVideoDisplays();
			display.display_index = -1;
			for (int i = 0; i < n_display; i++) {
				if (strstr(SDL_GetDisplayName(i), "OSVR") != nullptr) {
					display.display_index = i;
					break;
				}
			}
			if (display.display_index == -1)
				display.enabled = 0;
		}
		else {
			std::cout << "Failed to start display." << std::endl;
			display.enabled = 0;
		}
	}

	if (!display.enabled && !window.enabled) {
		std::cout << "Activating window mode." << std::endl;
		window.enabled = 1;
	}

	if (window.enabled) {
		window.width = 640;
		window.height = 480;

		window.handle = SDL_CreateWindow(
			"Mapa Estelar (PC)",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			window.width,
			window.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

		window.context = SDL_GL_CreateContext(window.handle);
		glewInit();

		glClearColor(0, 0, 0, 1);

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	if (display.enabled) {
		SDL_GetDisplayBounds(display.display_index, &(display.bounds));

		display.handle = SDL_CreateWindow(
			"Mapa Estelar (HMD)",
			display.bounds.x,
			display.bounds.y,
			display.bounds.w,
			display.bounds.h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);
		
		//SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

		display.context = SDL_GL_CreateContext(display.handle);
		glewInit();

		glClearColor(0, 0, 0, 1);
		
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	return 1;
}


int RenderSystem::update() {
	osvr_context->update();

	if (window.enabled) {
		SDL_GL_MakeCurrent(window.handle, window.context);
		SDL_GL_SwapWindow(window.handle);

		glViewport(0, 0, window.width, window.height);
		glClear(GL_COLOR_BUFFER_BIT);

		renderAll();
	}

	if (display.enabled) {
		SDL_GL_MakeCurrent(display.handle, display.context);
		glClear(GL_COLOR_BUFFER_BIT);

		int n_viewer;
		int n_eye;
		int n_surface;

		n_viewer = display.config->getNumViewers();
		for (int i = 0; i < n_viewer; i++) {
			osvr::clientkit::Viewer viewer = display.config->getViewer(i);
			n_eye = viewer.getNumEyes();

			for (int j = 0; j < n_eye; j++) {
				osvr::clientkit::Eye eye = viewer.getEye(j);
				n_surface = eye.getNumSurfaces();

				float view_mat[OSVR_MATRIX_SIZE];
				eye.getViewMatrix(OSVR_MATRIX_COLMAJOR, view_mat);

				for (int k = 0; k < n_surface; k++) {
					osvr::clientkit::Surface surface = eye.getSurface(k);
					osvr::clientkit::RelativeViewport viewport = surface.getRelativeViewport();

					glViewport(
						viewport.left,
						viewport.bottom,
						viewport.width,
						viewport.height);

					float proy_mat[OSVR_MATRIX_SIZE];
					surface.getProjectionMatrix(0.1, 2, OSVR_MATRIX_COLMAJOR, proy_mat);

					camera_matrix = glm::make_mat4(proy_mat) * glm::make_mat4(view_mat);

					renderAll();
				}
			}
		}

		SDL_GL_SwapWindow(display.handle);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
			return 0;
	}

	return 1;
}


int RenderSystem::renderAll() {
	int result = 1;

	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); i++) {
		result &= (*i)->update();
	}

	return result;
}


glm::mat4 RenderSystem::getCameraMatrix() {
	return camera_matrix;
}

glm::mat4 RenderSystem::getWorldMatrix() {
	return world_matrix;
}