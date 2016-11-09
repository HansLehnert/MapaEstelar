#include "RenderSystem.h"

#include <iostream>
#include <list>

#include <SDL.h>
#include <osvr\ClientKit\Context.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "GraphicComponent.h"

RenderSystem::RenderSystem() :
	camera_matrix(1),
	world_matrix(1),
	zoom_dir(0) {

	float z_far = 1000.f;
	float z_near = 0.1f;

	zoom = glm::vec2(1, 1);
	zoom_target = glm::vec2(1, 1);

	camera_matrix[0][0] = 9.f / 16.f * 2;
	camera_matrix[1][1] = 1.f * 2;
	camera_matrix[2][2] = 1.f;
	camera_matrix[2][3] = (z_far + z_near) / (z_far - z_near);
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
		window.width = 800;//Mover a configuracion por linea de comando
		window.height = 450;

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

	glClearColor(0, 0.02, 0.05, 1);
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

		glGenTextures(2, frame_texture);

		for (int i = 0; i < 2; i++) {
			surface[i] = new osvr::clientkit::Surface(display.config->getSurface(0, i, 0));

			surface_viewport[i] = surface[i]->getRelativeViewport();

			glBindTexture(GL_TEXTURE_2D, frame_texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface_viewport[i].width + 2, surface_viewport[i].height + 2, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);//Solucion parche, arreglar
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			//Mapa de distorcion
			glm::vec2 center;
			std::vector<float> k;
			if (i == 0) {
				center = glm::vec2(0.471, 0.5); //Hardcoded
				k = { 0.f, 1.f, -1.74f, 5.15f, -1.27f, -2.23f };
			}
			else {
				center = glm::vec2(0.529, 0.5);
				k = { 0.f, 1.f, -1.74f, 5.15f, -1.27f, -2.23f };
			}

			distortion_mesh[i] = generateDistortionMesh(64, 64, center, k);
		}
		//Falta agregar depth buffers
	}

	glGenVertexArrays(1, &vao_eye);
	glBindVertexArray(vao_eye);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	distortion_program = GLProgram::getProgram("distortion");

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

			glViewport(1, 1, surface_viewport[i].width, surface_viewport[i].height);

			//Calcular matriz de camara
			osvr::clientkit::Eye eye = display.config->getEye(0, surface[i]->getEyeID());

			float view_mat[OSVR_MATRIX_SIZE];
			float proy_mat[OSVR_MATRIX_SIZE];
			eye.getViewMatrix(OSVR_MATRIX_COLMAJOR, view_mat);
			surface[i]->getProjectionMatrix(0.01f, 1000000.f, OSVR_MATRIX_COLMAJOR, proy_mat);
			camera_matrix = glm::make_mat4(proy_mat) * glm::make_mat4(view_mat);
			
			glm::mat4 zoom_matrix(1);
			zoom_matrix[0][0] = zoom.x;
			zoom_matrix[1][1] = zoom.x;
			camera_matrix = zoom_matrix * camera_matrix;

			renderAll();
		}

		//Dibujar superficies
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vao_eye);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(distortion_program->id);

		glUniform1i(distortion_program->uniform["frame"].loc, 0);
		for (int i = 0; i < 2; i++) {
			glViewport(
				surface_viewport[i].left,
				surface_viewport[i].bottom,
				surface_viewport[i].width,
				surface_viewport[i].height
			);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frame_texture[i]);

			glBindBuffer(GL_ARRAY_BUFFER, distortion_mesh[i].vertex_buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, distortion_mesh[i].index_buffer);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

			glDrawElements(GL_TRIANGLES, distortion_mesh[i].index_length, GL_UNSIGNED_INT, 0);
		}

		SDL_GL_SwapWindow(display.handle);
	}

	//Dibujar en pantalla
	if (window.enabled) {
		SDL_GL_MakeCurrent(window.handle, render_context);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vao_common);

		glClear(GL_COLOR_BUFFER_BIT);

		if (display.enabled) { //Si el display está activado dibujar imágenes de ojos
			glBindVertexArray(vao_eye);

			glUseProgram(distortion_program->id);

			glUniform1i(distortion_program->uniform["frame"].loc, 0);
			for (int i = 0; i < 2; i++) {
				glViewport(
					surface_viewport[i].left * window.width / display.bounds.w,
					surface_viewport[i].bottom * window.height / display.bounds.h,
					surface_viewport[i].width * window.width / display.bounds.w,
					surface_viewport[i].height * window.height / display.bounds.h
				);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frame_texture[i]);

				glBindBuffer(GL_ARRAY_BUFFER, distortion_mesh[i].vertex_buffer);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, distortion_mesh[i].index_buffer);

				glDrawElements(GL_TRIANGLES, distortion_mesh[i].index_length, GL_UNSIGNED_INT, 0);
			}
		}
		else { //Dibujar escena en otro caso
			glViewport(0, 0, window.width, window.height);

			renderAll();
		}
		
		SDL_GL_SwapWindow(window.handle);
	}


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
			return 0;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				key_status[0] = e.type;
				break;
			case SDLK_LEFT:
				key_status[1] = e.type;
				break;
			case SDLK_UP:
				key_status[2] = e.type;
				break;
			case SDLK_DOWN:
				key_status[3] = e.type;
				break;
			case SDLK_q:
				key_status[4] = e.type;
				break;
			case SDLK_e:
				key_status[5] = e.type;
				break;
			}
		}
	}

	//Mover a clase Camera
	if (camera_dir.x == 0) {
		if (key_status[0] == SDL_KEYDOWN)
			camera_dir.x = -1;
		else if (key_status[1] == SDL_KEYDOWN)
			camera_dir.x = 1;
	}
	else if (camera_dir.x == -1 && key_status[0] == SDL_KEYUP) {
		if (key_status[1] == SDL_KEYDOWN)
			camera_dir.x = 1;
		else
			camera_dir.x = 0;
	}
	else if (camera_dir.x == 1 && key_status[1] == SDL_KEYUP) {
		if (key_status[0] == SDL_KEYDOWN)
			camera_dir.x = -1;
		else
			camera_dir.x = 0;
	}

	if (camera_dir.y == 0) {
		if (key_status[2] == SDL_KEYDOWN)
			camera_dir.y = 1;
		else if (key_status[3] == SDL_KEYDOWN)
			camera_dir.y = -1;
	}
	else if (camera_dir.y == 1 && key_status[2] == SDL_KEYUP) {
		if (key_status[3] == SDL_KEYDOWN)
			camera_dir.y = -1;
		else
			camera_dir.y = 0;
	}
	else if (camera_dir.y == -1 && key_status[3] == SDL_KEYUP) {
		if (key_status[2] == SDL_KEYDOWN)
			camera_dir.y = 1;
		else
			camera_dir.y = 0;
	}

	if (zoom_dir == 0) {
		if (key_status[4] == SDL_KEYDOWN)
			zoom_dir = 1;
		else if (key_status[5] == SDL_KEYDOWN)
			zoom_dir = -1;
	}
	else if (zoom_dir == 1 && key_status[4] == SDL_KEYUP) {
		if (key_status[5] == SDL_KEYDOWN)
			zoom_dir = -1;
		else
			zoom_dir = 0;
	}
	else if (zoom_dir == -1 && key_status[5] == SDL_KEYUP) {
		if (key_status[4] == SDL_KEYDOWN)
			zoom_dir = 1;
		else
			zoom_dir = 0;
	}

	camera_speed = (camera_speed + 0.1f * camera_dir) * 0.95f;

	if (zoom_dir == 1)
		zoom_target *= 1.02f;
	else if (zoom_dir == -1)
		zoom_target /= 1.02f;

	zoom = zoom_target * 0.4f + zoom * 0.6f;

	world_matrix = glm::rotate(glm::mat4(1), camera_speed.x, glm::vec3(0, 1, 0)) * world_matrix;
	world_matrix = glm::rotate(glm::mat4(1), camera_speed.y, glm::vec3(1, 0, 0)) * world_matrix;

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

GLuint RenderSystem::generateDistortionMap(int width, int height, glm::vec2 center, std::vector<float> k) {
	glm::vec3* texture_data = new glm::vec3[width * height];

	for (int i = 0; i < width; i++) {
		float x = (float)i / (width - 1);
		for (int j = 0; j < height; j++) {
			float y = (float)j / (height - 1);

			glm::vec2 offset = glm::vec2(x, y) - center;
			float r = glm::length(offset);
			float d = 0;
			for (int m = k.size() - 1; m >= 0; m--) {
				d *= r;
				d += k[m];
			}
			texture_data[i + width * j].r = center.x + d * offset.x / r;
			texture_data[i + width * j].g = center.y + d * offset.y / r;
		}
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, texture_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return texture;
}

GLMesh RenderSystem::generateDistortionMesh(int width, int height, glm::vec2 center, std::vector<float> k) {
	GLMesh mesh;

	mesh.vertex_length = width * height;
	mesh.index_length = (width - 1) * (height - 1) * 6;

	glm::vec4* vertex_data = new glm::vec4[mesh.vertex_length];
	unsigned int* index_data = new unsigned int[mesh.index_length];

	for (int i = 0; i < width; i++) {
		float x = (float)i / (width - 1);
		for (int j = 0; j < height; j++) {
			float y = (float)j / (height - 1);

			glm::vec2 offset = glm::vec2(x, y) - center;
			float r = glm::length(offset);
			float d = 0;
			for (int m = k.size() - 1; m >= 0; m--) {
				d *= r;
				d += k[m];
			}
			vertex_data[i + width * j].x = 2 * x - 1;
			vertex_data[i + width * j].y = 2 * y - 1;
			vertex_data[i + width * j].z = center.x + d * offset.x / r;
			vertex_data[i + width * j].w = center.y + d * offset.y / r;
		}
	}

	for (int i = 0; i < width - 1; i++) {
		for (int j = 0; j < height - 1; j++) {
			unsigned int* base = index_data + (i + j * (width - 1)) * 6;
			base[0] = width * j + i;
			base[1] = width * (j + 1) + i;
			base[2] = width * j + i + 1;
			base[3] = width * j + i + 1;
			base[4] = width * (j + 1) + i;
			base[5] = width * (j + 1) + i + 1;
		}
	}

	glGenBuffers(1, &mesh.vertex_buffer);
	glGenBuffers(1, &mesh.index_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertex_length * sizeof(glm::vec4), vertex_data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index_length * sizeof(unsigned int), index_data, GL_STATIC_DRAW);

	return mesh;
}