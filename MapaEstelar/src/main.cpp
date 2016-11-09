#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "display\RenderSystem.h"
#include "StarSet.h"

int loadStarData(std::string file_name, std::vector<Star>* data) {
	std::ifstream star_file;
	
	star_file.open(("rsrc/bin/dataset/" + file_name + ".bin").c_str(), std::fstream::binary);

	if (star_file.is_open()) {
		while (!star_file.eof()) {
			Star new_star;
			star_file.read((char*)&new_star, sizeof(new_star));

			new_star.color /= 256.f;
			new_star.size = 1 * log(new_star.size) - 4;
			if (new_star.size < 1) {
				new_star.color *= std::max(0.6f, new_star.size);
				new_star.size = 1;
			}

			//new_star.size = 4;

			data->push_back(new_star);
		}

		star_file.close();
		return 1;
	}

	star_file.open("rsrc/dataset/" + file_name);

	if (!star_file.is_open())
		return 0;

	while (!star_file.eof()) {
		std::string line;
		std::getline(star_file, line);

		if (line.length() > 0) {
			std::stringstream line_stream(line);
			std::string value_str;
			unsigned int index;

			Star new_star;

			std::getline(line_stream, value_str, ',');
			index = std::stoi(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.color.r = (float)std::stoi(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.color.g = (float)std::stoi(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.color.b = (float)std::stoi(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.position.x = std::stof(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.position.y = std::stof(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.position.z = std::stof(value_str);
			std::getline(line_stream, value_str, ',');
			new_star.size = std::stof(value_str);

			while(data->size() < index + 1)
				data->push_back(new_star);
		}
	}
	star_file.close();

	std::ofstream bin_file("rsrc/bin/dataset/" + file_name + ".bin", std::fstream::binary);
	bin_file.write((char*)&(*data)[0], sizeof(Star) * data->size());
	bin_file.close();

	return 1;
}

int loadConstellationData(std::string file_name, std::vector<Constellation>* data) {
	std::ifstream constellation_file("rsrc/dataset/" + file_name);

	if (!constellation_file.is_open())
		return 0;

	Constellation new_constellation;
	int last_index = -1;
	while (!constellation_file.eof()) {
		std::string line;

		std::getline(constellation_file, line);

		if (line.length() > 0) {
			std::stringstream line_stream(line);
			std::string name;
			std::string index_str;
			int index;

			std::getline(line_stream, name, ',');
			std::getline(line_stream, index_str, ',');

			if (new_constellation.name != name) {
				if (new_constellation.name.length() > 0) {
					data->push_back(new_constellation);
				}
				new_constellation.name = name;
				new_constellation.indices.clear();
				last_index = -1;
			}

			if (index_str.length() > 0) {
				index = std::stoi(index_str);
				if (last_index != -1) {
					new_constellation.indices.push_back(last_index);
					new_constellation.indices.push_back(index);
				}
				last_index = index;
			}
			else {
				last_index = -1;
			}
		}
	}

	constellation_file.close();
	return 1;
}


int main(int argc, char** argv) {
	RenderSystem render_sys;
	render_sys.init();

	StarSet main_set(&render_sys);

	if (loadStarData("DataStars.csv", &main_set.star_data)) {
		main_set.loadStars();
	}
	else {
		std::cout << "Failed to load star data." << std::endl;
		return 0;
	}
	
	if (loadConstellationData("ConstDesignation.csv", &main_set.constellation_data)) {
		main_set.loadConstellations();
	}
	else {
		std::cout << "Failed to load constellation data." << std::endl;
	}
	/*
	for (int i = 0; i < 1000; i++) {
		Star star;
		float a = 3.14f * 2 * (rand() / (float)RAND_MAX);
		float b = 3.14f * (rand() / (float)RAND_MAX);
		float r = 1.6f + 0.4f * (rand() / (float)RAND_MAX);
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

	main_set.loadStars();*/
	
	/*for (int i = 0; i < 10; i++) {
		Constellation constellation;
		constellation.color = { 1.f, 1.f, 1.f, 1.f };
		int n = rand() % 10;
		int last = rand() % main_set.star_data.size();
		for (int j = 0; j < n; j++) {
			constellation.indices.push_back(last);
			last = rand() % main_set.star_data.size();
			constellation.indices.push_back(last);
		}
		main_set.constellation_data.push_back(constellation);
	}*/

	while (render_sys.update()) {
		continue;
	}

	return 1;
}