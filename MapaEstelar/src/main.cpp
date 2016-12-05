#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "display\RenderSystem.h"
#include "display\text\Label.h"

#include "input\KeyboardMouseInputSystem.h"
#include "input\HighlightInput.h"

#include "DataManager.h"
#include "StarSet.h"
#include "CameraObject.h"

int loadStarData(std::string file_name, std::vector<Star>* data) {
	std::ifstream star_file;
	
	star_file.open(("rsrc/bin/dataset/" + file_name + ".bin").c_str(), std::fstream::binary);

	if (star_file.is_open()) {
		while (!star_file.eof()) {
			Star new_star;
			star_file.read((char*)&new_star, sizeof(new_star));

			new_star.position.x *= 100;
			new_star.position.y *= 100;
			new_star.position.z *= 100;
			new_star.color /= 256.f;
			new_star.color.a = 1;
			new_star.size = 1 * log(new_star.size) - 3;
			if (new_star.size < 2) {
				//new_star.color *= std::max(0.6f, new_star.size);
				new_star.color.a = std::max(0.1f, new_star.size / 2);
				new_star.size = 2;
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
	KeyboardMouseInputSystem input_sys;

	render_sys.init();
	render_sys.bindInput(&input_sys);

	CameraObject camera(&render_sys, &input_sys);
	StarSet main_set(&render_sys);
	DataManager data_manager;
	std::vector<Object*> constellation_label;

	if (loadStarData("DataStars.csv", &main_set.star_data)) {
		main_set.loadStars();
	}
	else {
		std::cout << "Failed to load star data." << std::endl;
		return 0;
	}
	
	if (loadConstellationData("ConstDesignation.csv", &main_set.constellation_data)) {
		main_set.loadConstellations();

		for (auto constellation : main_set.constellation_data) {
			Object* new_object = new Object();

			HighlightInput* new_input = new HighlightInput(&input_sys,
				                                           new_object,
				                                           InputSystem::Priority::EQUAL);

			Label* new_label = new Label(&render_sys,
				                         new_object,
				                         "rsrc/font/MuseoSans-500.otf",
				                         data_manager.getName(constellation.name));

			new_label->position_inactive = constellation.position * 100.f;
			new_label->position_inactive.w = 1;
			new_label->position_active = constellation.position * 10.f;
			new_label->position_active.w = 1;

			new_label->color_inactive = glm::vec4(0.8f, 0.9f, 1.0f, 0.8f);
			new_label->color_active = glm::vec4(0.9f, 1.0f, 0.1f, 1.0f);

			new_label->size_inactive = glm::vec2(0.04f);
			new_label->size_active = glm::vec2(0.05f);

			new_label->setWhitespaceWidth(0.5);

			new_object->input_component = new_input;
			new_object->graphic_component = new_label;
			constellation_label.push_back(new_object);
		}
	}
	else {
		std::cout << "Failed to load constellation data." << std::endl;
	}

	float t = 0;
	while (render_sys.update()) {
		input_sys.update();
	}

	return 1;
}