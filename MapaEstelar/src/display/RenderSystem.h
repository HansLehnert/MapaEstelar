#pragma once

#include <osvr\ClientKit\ClientKit.h>
#include <osvr\ClientKit\Display.h>
#include <SDL_video.h>
#include <glm\glm.hpp>
#include <GL\glew.h>

#include "../core/System.h"
#include "GLProgram.h"

class RenderSystem : public System {
public:
	RenderSystem();
	~RenderSystem();

	int init();
	int update();
	int renderAll();

	glm::mat4 getCameraMatrix();
	glm::mat4 getWorldMatrix();

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
	GLuint plane_buffer;
	GLProgram* frame_program;
	GLuint tex_uniform;
};

