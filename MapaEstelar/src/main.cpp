#include <iostream>
#include <vector>

#include "display\RenderSystem.h"
#include "StarSet.h"

int main(int argc, char** argv) {
	RenderSystem render_sys;
	render_sys.init();

	std::vector<Star> star_data;
	for (int i = 0; i < 1000; i++) {
		Star star;
		star.position.x = (rand() / (float)RAND_MAX) * 2 - 1;
		star.position.y = (rand() / (float)RAND_MAX) * 2 - 1;
		star.position.z = (rand() / (float)RAND_MAX) * 2 - 1;
		star.position.w = 1;
		star.color = { 1, 1, 1 };
		star.size = 1;
		star_data.push_back(star);
	}

	StarSet main_set(&render_sys);
	main_set.load(star_data);

	while (render_sys.update()) {
		continue;
	}

	return 0;
}