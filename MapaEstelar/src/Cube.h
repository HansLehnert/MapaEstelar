#pragma once

#include <GL\glew.h>

#include "display\GraphicComponent.h"

struct Point {
	//Posicion en coordenadas cartesianas
	//(a�adir otra representaci�n?)
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

	float size;
};

class Cube : public GraphicComponent {
public:
	Cube(RenderSystem*);

	int update();
	//Funci�n de dibujo
	int render();

private:
	GLuint data_buffer;
};