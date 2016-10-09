#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 tex_coord;

uniform mat4 model_matrix;
uniform mat4 world_matrix;
uniform mat4 camera_matrix;

void main() {
	gl_Position = camera_matrix * world_matrix * position;
	gl_PointSize = 4.0;
}