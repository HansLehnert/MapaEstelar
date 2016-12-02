#pragma once

#include <map>
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
	Font();

	int font_size;
	GLuint getTextureId();
	const Character* getCharData();
	
	static Font* getFont(std::string);
private:
	Font(std::string);
	static void initFreetype();

	GLuint texture;
	Character char_data[256];

	FT_Face face;

	static std::map<std::string, Font> font_cache;
};