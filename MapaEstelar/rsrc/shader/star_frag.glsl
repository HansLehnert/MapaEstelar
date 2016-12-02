#version 330

in vec4 star_color;

out vec4 frag_color;

void main() {
	frag_color = star_color;
	float radius = length(2 * (gl_PointCoord - vec2(0.5)));
	//frag_color.rgb = mix(vec3(1), star_color.rgb, 1 - radius);
	frag_color.a = (1 - radius) * star_color.a;
}