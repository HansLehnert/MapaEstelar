#pragma once

#include <vector>

#include <GL\glew.h>

#include "display\GraphicComponent.h"

struct Star {
	//Posicion en coordenadas cartesianas
	//(añadir otra representación?)
	//"w" debe ser 1
	struct {
		float x;
		float y;
		float z;
		float w;
	} position;

	//Color en formato RGB
	struct {
		float r;
		float g;
		float b;
		float a;
	} color;

	//Tamaño en pixeles
	float size;
};

class StarSet : public GraphicComponent {
public:
	StarSet(RenderSystem*);

	int update();
	//Función de dibujo
	int render();

	//Carga datos de las estrellas a buffers de OpenGL
	//a partir de un vector de estrellas
	int load(std::vector<Star>*);

private:
	GLuint data_buffer;

	int n_data;
};