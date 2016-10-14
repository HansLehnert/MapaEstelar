#version 330

in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D frame;
uniform sampler2D distortion_map;

void main() {
	frag_color = texture(frame, texture(distortion_map, tex_coord).xy);
	//frag_color = vec4(1, 0, 0, 1);
}