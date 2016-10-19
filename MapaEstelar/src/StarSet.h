#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "display\GraphicComponent.h"

struct Star {
	//Posicion en coordenadas cartesianas
	//(a�adir otra representaci�n?)
	//"w" debe ser 1
	glm::vec4 position;

	//Color en formato RGB
	glm::vec4 color;

	//Tama�o en pixeles
	float size;
};

struct Constellation {
	//Nombre de las constelac�on
	std::string name;

	//Pares de indices de las estrellas que forman los trazos
	std::vector<int> indices;

	//Color del trazo
	glm::vec4 color;

	//No asignar
	int loc;
};

class StarSet : public GraphicComponent {
public:
	StarSet(RenderSystem*);

	std::vector<Star>          star_data;
	std::vector<Constellation> constellation_data;

	int update();
	//Funci�n de dibujo
	int render();

	//Carga datos de las estrellas a buffers de OpenGL
	//a partir de un vector de estrellas
	int loadStars();
	//Carga de datos de constelaciones a partir de un vector de
	//constelaciones
	int loadConstellations();
private:
	GLuint star_buffer;
	GLuint constellation_buffer;

	int n_indices;
};