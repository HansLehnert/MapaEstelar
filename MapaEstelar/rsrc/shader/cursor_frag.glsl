#version 330

in vec4 vert_color;
in float progress;

out vec4 frag_color;

uniform float activation;

void main() {
	if (activation > progress) {
		frag_color = vert_color;
	}
	else {
		frag_color = vec4(0);
	}
}