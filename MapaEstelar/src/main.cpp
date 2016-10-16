#include <iostream>
#include <vector>

#include "display\RenderSystem.h"
#include "StarSet.h"

int main(int argc, char** argv) {
	RenderSystem render_sys;
	render_sys.init();

	std::vector<Star> star_data;
	for (int i = 0; i < 100000; i++) {
		Star star;
		float a = 3.14f * 2 * (rand() / (float)RAND_MAX);
		float b = 3.14f * (rand() / (float)RAND_MAX);
		float r = 1.6f + 0.4f * (rand() / (float)RAND_MAX);
		star.position.x = cos(a) * sin(b) * r;
		star.position.y = sin(a) * sin(b) * r;
		star.position.z = cos(b);
		star.position.w = 1;
		star.color.r = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.g = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.b = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.a = 1;
		star.size = 1 + (rand() / (float)RAND_MAX) * 4;
		star_data.push_back(star);
	}

	StarSet main_set(&render_sys);
	main_set.load(&star_data);

	while (render_sys.update()) {
		continue;
	}

	return 0;
}