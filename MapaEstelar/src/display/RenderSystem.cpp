#include "RenderSystem.h"

#include <iostream>
#include <list>

#include <SDL.h>
#include <osvr\ClientKit\Context.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\quaternion.hpp>

#include "GraphicComponent.h"

RenderSystem::RenderSystem() :
	base_camera_matrix(1),
	camera_matrix(1),
	world_matrix(1),
	input_system(nullptr) {

	float z_far = 1000.f;
	float z_near = 0.1f;

	base_camera_matrix[0][0] = 9.f / 16.f * 2;
	base_camera_matrix[1][1] = 1.f * 2;
	base_camera_matrix[2][2] = 1.f;
	base_camera_matrix[2][3] = (z_far + z_near) / (z_far - z_near);
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

	aspect_ratio.x = 450.0 / 800.0;
	aspect_ratio.y = 1.0;

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
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

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
		
		//Compartir contextos si la ventana est� habilitada
		if (window.enabled)
			SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

		display.context = SDL_GL_CreateContext(display.handle);
		render_context = display.context;

		//Correcci�n de relaci�n de aspecto
		aspect_ratio.x = 2 * 1080 / 1920.0;
		aspect_ratio.y = 1;
	}

	//Configuracion OpenGL
	glewInit();

	glClearColor(0.f, 0.02f, 0.05f, 0.f);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &vao_common);
	glBindVertexArray(vao_common);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
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

	//Resetear modificador externo de matrixz de c�mara.
	//Puede ser cambiada por alg�n componente en el siguiente paso
	camera_matrix = glm::mat4(1);

	//Actualizar todas las componentes gr�ficas
	updateAll();
	glm::mat4 camera_matrix_mod = camera_matrix;

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

			//Obtener matriz de c�mara correspondiente al HMD
			float view_mat[OSVR_MATRIX_SIZE];
			float proy_mat[OSVR_MATRIX_SIZE];
			eye.getViewMatrix(OSVR_MATRIX_COLMAJOR, view_mat);
			surface[i]->getProjectionMatrix(0.01f, 1000000.f, OSVR_MATRIX_COLMAJOR, proy_mat);
			base_camera_matrix = glm::make_mat4(proy_mat) * glm::make_mat4(view_mat);

			//Calcular la matriz de c�mara a utilizar para dibujar.
			//"base_camera_matrix" proviene del sistema mientras que "camera_matrix"
			//es un modificador externo
			camera_matrix = camera_matrix_mod * base_camera_matrix;

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

		if (display.enabled) { //Si el display est� activado dibujar im�genes de ojos
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

			camera_matrix = camera_matrix_mod * base_camera_matrix;

			renderAll();
		}
		
		SDL_GL_SwapWindow(window.handle);
	}


	//Manejar eventos, enviar eventos de entrada a sistema de entrada
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_CLOSE)
				return 0;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			if (input_system != nullptr) {
				Message input_message;
				input_message.type = MSG_SDL;
				input_message.sdl.source = nullptr;
				input_message.sdl.event = e;
				input_system->sendMessage(input_message);
			}
			break;
		default:
			break;
		}
	}

	
	//Actualizar pose
	if (display.enabled) {
		OSVR_Pose3 display_pose;
		display.config->getViewer(0).getPose(display_pose);

		glm::quat pose_quat;
		pose_quat.w = osvrQuatGetW(&display_pose.rotation);
		pose_quat.x = osvrQuatGetX(&display_pose.rotation);
		pose_quat.y = osvrQuatGetY(&display_pose.rotation);
		pose_quat.z = osvrQuatGetZ(&display_pose.rotation);

		pose = glm::mat3_cast(pose_quat);
	}
	else {
		pose = glm::mat3(1);
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


int RenderSystem::sendMessage(Message) {
	return 1;
}


int RenderSystem::bindInput(InputSystem* system) {
	input_system = system;
	return 1;
}


glm::mat4 RenderSystem::getCameraMatrix() {
	return base_camera_matrix;
}


glm::mat4 RenderSystem::getWorldMatrix() {
	return world_matrix;
}


glm::mat3 RenderSystem::getPose() {
	return pose;
}


glm::vec2 RenderSystem::getAspectRatio() {
	return aspect_ratio;
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