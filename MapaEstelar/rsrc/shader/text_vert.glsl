#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 tex_coord;
layout (location = 4) in float offset;

out vec2 glyph_uv;

uniform mat4 model_matrix;
uniform mat4 world_matrix;
uniform mat4 camera_matrix;

uniform vec4 base_position;

void main() {
	gl_Position = /*camera_matrix * world_matrix * */base_position;
	gl_Position.xyz /= gl_Position.w;
	gl_Position.w = 1;
	gl_Position.xy += position.xy * 0.1;
	glyph_uv = tex_coord;
}