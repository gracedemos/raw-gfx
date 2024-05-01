#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 translate;

void main() {
	gl_Position = translate * vec4(aPos, 1.0);
}
