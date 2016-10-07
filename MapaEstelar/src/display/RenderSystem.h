#pragma once

#include <osvr\ClientKit\ClientKit.h>
#include <osvr\ClientKit\Display.h>
#include <SDL_video.h>
#include <glm\glm.hpp>

#include "../core/System.h"

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
	//OSVR
	osvr::clientkit::ClientContext* osvr_context;

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
};

