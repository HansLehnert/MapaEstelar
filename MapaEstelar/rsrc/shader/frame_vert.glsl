#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex;

out vec2 tex_coord;

void main() {
	gl_Position.xy = position;
	gl_Position.zw = vec2(0, 1);
	tex_coord = tex;
}