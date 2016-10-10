#include "RenderSystem.h"

#include <iostream>
#include <list>

#include <SDL.h>
#include <osvr\ClientKit\Context.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "GraphicComponent.h"

const float PLANE_MESH[] = {
	1,	1,	1,	1,
	1,	-1,	1,	0,
	-1,	-1,	0,	0,
	-1,	1,	0,	1
};

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
	window.enabled = 1;
	display.enabled = 1;

	glewExperimental = GL_TRUE;
	glewInit();

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

	//Habilitar ventana si no se encuentra HMD
	if (!display.enabled && !window.enabled) {
		std::cout << "Activating window mode." << std::endl;
		window.enabled = 1;
	}

	//Hints OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//Crear contexto para ventana
	if (window.enabled) {
		window.width = 640;//Mover a configuracion por linea de comando
		window.height = 480;

		window.handle = SDL_CreateWindow(
			"Mapa Estelar (Ventana)",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			window.width,
			window.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		window.context = SDL_GL_CreateContext(window.handle);
		render_context = window.context;
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
		
		//Compartir contextos si la ventana está habilitada
		if (window.enabled)
			SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

		display.context = SDL_GL_CreateContext(display.handle);
		render_context = display.context;
	}

	//Configuracion OpenGL
	glewInit();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glGenVertexArrays(1, &vao_common);
	glBindVertexArray(vao_common);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(4);

	//Configurar framebuffers
	glGenFramebuffers(1, &frame_buffer);

	if (display.enabled) {
		//De momento basta asumir 1 display, 2 ojos y 1 superficie por display;
		//surface = new osvr::clientkit::Surface[2];

		glGenTextures(2, frame_texture);

		for (int i = 0; i < 2; i++) {
			surface[i] = new osvr::clientkit::Surface(display.config->getSurface(0, i, 0));

			surface_viewport[i] = surface[i]->getRelativeViewport();

			glBindTexture(GL_TEXTURE_2D, frame_texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface_viewport[i].width, surface_viewport[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		//Falta agregar depth buffers
	}

	glGenVertexArrays(1, &vao_eye);
	glBindVertexArray(vao_eye);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &plane_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, plane_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PLANE_MESH), &(PLANE_MESH[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	frame_program = GLProgram::getProgram("frame");
	tex_uniform = glGetUniformLocation(frame_program->id, "frame_texture");

	return 1;
}


int RenderSystem::update() {
	osvr_context->update();

	//Dibujar en HMD
	if (display.enabled) {
		SDL_GL_MakeCurrent(display.handle, render_context);

		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
		glBindVertexArray(vao_common);

		for (int i = 0; i < 2; i++) { //2 ojos
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frame_texture[i], 0);
			glClear(GL_COLOR_BUFFER_BIT);

			const GLuint draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, draw_buffers);

			glViewport(0, 0, surface_viewport[i].width, surface_viewport[i].height);

			//Calcular matriz de camara
			osvr::clientkit::Eye eye = display.config->getEye(0, surface[i]->getEyeID());

			float view_mat[OSVR_MATRIX_SIZE];
			float proy_mat[OSVR_MATRIX_SIZE];
			eye.getViewMatrix(OSVR_MATRIX_COLMAJOR, view_mat);
			surface[i]->getProjectionMatrix(0.1f, 2.f, OSVR_MATRIX_COLMAJOR, proy_mat);
			camera_matrix = glm::make_mat4(proy_mat) * glm::make_mat4(view_mat);

			renderAll();
		}

		//Dibujar superficies
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vao_eye);

		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glUseProgram(frame_program->id);

		glUniform1i(tex_uniform, 0);
		for (int i = 0; i < 2; i++) {
			glViewport(
				surface_viewport[i].left,
				surface_viewport[i].bottom,
				surface_viewport[i].width,
				surface_viewport[i].height
			);

			glBindTexture(GL_TEXTURE_2D, frame_texture[i]);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}

		SDL_GL_SwapWindow(display.handle);
	}
	/*if (display.enabled) {
		SDL_GL_MakeCurrent(display.handle, render_context);
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
	}*/

	//Dibujar en pantalla
	if (window.enabled) {
		SDL_GL_MakeCurrent(window.handle, render_context);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vao_common);

		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, window.width, window.height);

		renderAll();
		SDL_GL_SwapWindow(window.handle);
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
		result &= ((GraphicComponent*)(*i))->render();
	}

	return result;
}


glm::mat4 RenderSystem::getCameraMatrix() {
	return camera_matrix;
}

glm::mat4 RenderSystem::getWorldMatrix() {
	return world_matrix;
}