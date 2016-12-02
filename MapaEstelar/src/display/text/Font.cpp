#include "Font.h"

#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library library;

std::map<std::string, Font> Font::font_cache;

Font::Font() {}

Font::Font(std::string file_name) {
	if (library == nullptr)
		initFreetype();

	FT_Error error;

	error = FT_New_Face(library, file_name.c_str(), 0, &face);
	if (error) {
		std::cout << "Failed to load " << file_name << "font." << std::endl;
	}

	font_size = 32;

	FT_Set_Pixel_Sizes(face, 0, font_size); //Tamaño de la fuente en pixeles

	//Mapa de bits para almacenar caracteres
	int bitmap_width = 16 * font_size;
	int bitmap_height = 16 * font_size;
	unsigned char* bitmap = new unsigned char[bitmap_width * bitmap_height];
	memset(bitmap, 0, bitmap_width * bitmap_height);

	float mesh_data[256][4][6]; //Número de caracteres * puntos * (dimensiones puntos + texturas)
	memset(&mesh_data[0][0][0], 0, sizeof(mesh_data));

	//Generar mapas de bits para cada caracter de ASCII extendido
	for (int c = 0; c < 256; c++) {
		unsigned int glyph_index = FT_Get_Char_Index(face, c);
		FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		//Blitting
		FT_Bitmap* glyph_bitmap = &(face->glyph->bitmap);
		for (unsigned int i = 0; i < glyph_bitmap->rows; i++) {
			for (unsigned int j = 0; j < glyph_bitmap->width; j++) {
				int pixel_offset = bitmap_width * (i + c / 16 * font_size) + j + (c % 16) * font_size;
				bitmap[pixel_offset] = glyph_bitmap->buffer[i * glyph_bitmap->width + j];
			}
		}

		//Generar envolturas de caracteres
		char_data[c].width = (float)glyph_bitmap->width;
		char_data[c].height = (float)glyph_bitmap->rows;
		char_data[c].tex_coord[0].x = ((c % 16) * font_size) / (float)bitmap_width;
		char_data[c].tex_coord[0].y = ((c / 16) * font_size + glyph_bitmap->rows) / (float)bitmap_width;
		char_data[c].tex_coord[1].x = ((c % 16) * font_size + glyph_bitmap->width) / (float)bitmap_width;
		char_data[c].tex_coord[1].y = ((c / 16) * font_size + glyph_bitmap->rows) / (float)bitmap_width;
		char_data[c].tex_coord[2].x = ((c % 16) * font_size) / (float)bitmap_width;
		char_data[c].tex_coord[2].y = ((c / 16) * font_size) / (float)bitmap_width;
		char_data[c].tex_coord[3].x = ((c % 16) * font_size + glyph_bitmap->width) / (float)bitmap_width;
		char_data[c].tex_coord[3].y = ((c / 16) * font_size) / (float)bitmap_width;
		char_data[c].offset.y = (float)(glyph_bitmap->rows - face->glyph->bitmap_top);
	}

	//Almacenar textura en buffer
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, bitmap_width, bitmap_height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Font::initFreetype() {
	FT_Error error;

	error = FT_Init_FreeType(&library);
	if (error) {
		std::cout << "Failed to initialize Freetype library" << std::endl;
	}
}

Font* Font::getFont(std::string name) {
	if (font_cache.find(name) == font_cache.end()) {
		Font new_font(name);

		font_cache[name] = new_font;
	}
	return &font_cache[name];
}

GLuint Font::getTextureId() {
	return texture;
}

const Character* Font::getCharData() {
	return char_data;
}