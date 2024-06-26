#version 330

layout (location = 0) in vec3 aPos;

uniform mat3 mult;

void main() {
	gl_Position = vec4(mult * aPos, 1.0);
}
