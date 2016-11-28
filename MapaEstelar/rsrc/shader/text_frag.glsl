#version 330

in vec2 glyph_uv;

out vec4 frag_color;

uniform vec4 font_color;
uniform sampler2D font_tex;

void main() {
	frag_color = font_color;
	frag_color.a *= texture(font_tex, glyph_uv).r;
}