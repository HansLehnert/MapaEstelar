#version 330

in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D frame_texture;

void main() {
	frag_color = texture(frame_texture, tex_coord);
	//frag_color = vec4(1, 0, 0, 1);
}