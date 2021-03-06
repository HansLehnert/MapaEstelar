#pragma once

#include <osvr\ClientKit\ClientKit.h>
#include <osvr\ClientKit\Display.h>
#include <SDL_video.h>
#include <glm\glm.hpp>
#include <GL\glew.h>

#include "..\core\System.h"
#include "..\input\InputSystem.h"
#include "GLProgram.h"
#include "GLMesh.h"

class RenderSystem : public System {
public:
	RenderSystem();
	~RenderSystem();

	int init();
	int update();
	int sendMessage(Message);
	int renderAll();

	int bindInput(InputSystem*);

	glm::mat4 getCameraMatrix();
	glm::mat4 getWorldMatrix();
	glm::mat3 getPose();
	glm::vec2 getAspectRatio();

	glm::mat4 camera_matrix;
	glm::mat4 world_matrix;
private:
	//VAO
	GLuint vao_common;
	GLuint vao_eye;

	//OSVR
	osvr::clientkit::ClientContext* osvr_context;
	osvr::clientkit::Surface* surface[2];
	osvr::clientkit::RelativeViewport surface_viewport[2];

	SDL_GLContext render_context;

	//Window info
	struct {
		int enabled;
		int width;
		int height;
		SDL_Window* handle;
		SDL_GLContext context;
	} window;

	//HMD info
	struct {
		int enabled;
		osvr::clientkit::DisplayConfig* config;

		int display_index;
		SDL_Rect bounds;
		SDL_Window* handle;
		SDL_GLContext context;
	} display;

	//Framebuffers
	GLuint frame_buffer;
	GLuint frame_texture[2];

	GLMesh distortion_mesh[2];
	GLProgram* distortion_program;

	GLuint generateDistortionMap(int, int, glm::vec2, std::vector<float>);
	GLMesh generateDistortionMesh(int, int, glm::vec2, std::vector<float>);

	//Sistema de entrada
	InputSystem* input_system;

	//Matriz de camara base
	//Obtenida de posici�n del visor, o posicion inicial
	glm::mat4 base_camera_matrix;

	//Pose del visor
	glm::mat3 pose;

	//Correcci�n de relaci�n de aspecto
	glm::vec2 aspect_ratio;
};

