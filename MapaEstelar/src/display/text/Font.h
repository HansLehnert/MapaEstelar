#pragma once

#include <string>

#include <GL\glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm\glm.hpp>

#include "..\GLMesh.h"

struct Character {
	float width;
	float height;
	glm::vec2 tex_coord[4];
	glm::vec2 offset;
};

class Font {
public:
	Font(std::string);

	GLuint texture;
	Character char_data[256];

	int font_size;
private:
	static void initFreetype();

	FT_Face face;
};