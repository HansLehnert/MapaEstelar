#include <iostream>
#include <vector>

#include "display\RenderSystem.h"
#include "StarSet.h"
#include "Cube.h"

int main(int argc, char** argv) {
	RenderSystem render_sys;
	render_sys.init();

	StarSet main_set(&render_sys);

	for (int i = 0; i < 1000; i++) {
		Star star;
		float a = 3.14f * 2 * (rand() / (float)RAND_MAX);
		float b = 3.14f * (rand() / (float)RAND_MAX);
		float r = 0.1f + 1.9f * (rand() / (float)RAND_MAX);
		star.position.x = cos(a) * sin(b) * r;
		star.position.y = sin(a) * sin(b) * r;
		star.position.z = cos(b) * r;
		star.position.w = 1;
		star.color.r = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.g = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.b = (rand() / (float)RAND_MAX) * 0.6f + 0.4f;
		star.color.a = 1;
		star.size = 1 + (rand() / (float)RAND_MAX) * 4;
		main_set.star_data.push_back(star);
	}
	
	for (int i = 0; i < 10; i++) {
		Constellation constellation;
		constellation.color = { 1.f, 1.f, 1.f };
		int n = rand() % 10;
		int last = rand() % main_set.star_data.size();
		for (int j = 0; j < n; j++) {
			constellation.indices.push_back(last);
			last = rand() % main_set.star_data.size();
			constellation.indices.push_back(last);
		}
		main_set.constellation_data.push_back(constellation);
	}

	main_set.loadStars();
	main_set.loadConstellations();

	while (render_sys.update()) {
		continue;
	}

	return 0;
}