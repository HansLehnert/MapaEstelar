#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "display\GraphicComponent.h"
#include "WindowObject.h"

struct Star {
	//Posicion en coordenadas cartesianas
	//(añadir otra representación?)
	//"w" debe ser 1
	glm::vec4 position;

	//Color en formato RGB
	glm::vec4 color;

	//Tamaño en pixeles
	float size;
};

struct Constellation {
	//Nombre de las constelacíon
	std::string name;

	//Pares de indices de las estrellas que forman los trazos
	std::vector<int> indices;

	//Color del trazo
	glm::vec4 color;

	//Posicion media de la constelación
	glm::vec4 position;

	//No asignar
	int loc;
};

class StarSet : public GraphicComponent {
public:
	StarSet(RenderSystem*, Object* = nullptr);

	std::vector<Star>          star_data;
	std::vector<Constellation> constellation_data;

	int update();
	int sendMessage(Message);
	//Función de dibujo
	int render();

	//Carga datos de las estrellas a buffers de OpenGL
	//a partir de un vector de estrellas
	int loadStars();
	//Carga de datos de constelaciones a partir de un vector de
	//constelaciones
	int loadConstellations();

	//Ventana de información
	WindowObject* window;
private:
	GLuint star_buffer;
	GLuint constellation_buffer;

	GLProgram* program_stars;
	GLProgram* program_constellations;

	int n_indices;
};