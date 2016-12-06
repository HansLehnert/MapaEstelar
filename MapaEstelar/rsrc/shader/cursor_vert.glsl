#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 tex_coord;
layout (location = 4) in float size;

out vec4 vert_color;
out float progress;

uniform mat4 model_matrix;
uniform mat4 world_matrix;
uniform mat4 camera_matrix;

uniform vec2 base_position;
uniform vec4 base_color;
uniform vec2 scale;

void main() {
	gl_Position = vec4(base_position, 0, 0) + position * vec4(scale, 0, 1);
	vert_color = base_color;
	progress = size;
}