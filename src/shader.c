#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

char * read_shader_text(const char *path) {
	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char *data = malloc(size * sizeof(char));
	fread(data, size, 1, file);
	fclose(file);

	return data;
}

Shader load_shader(const char *vert_path, const char *frag_path) {
	const char *vert_source = read_shader_text(vert_path);
	const char *frag_source = read_shader_text(frag_path);

	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vert_shader, 1, &vert_source, NULL);
	glShaderSource(frag_shader, 1, &frag_source, NULL);
	glCompileShader(vert_shader);
	glCompileShader(frag_shader);

	GLuint id = glCreateProgram();
	glAttachShader(id, vert_shader);
	glAttachShader(id, frag_shader);
	glLinkProgram(id);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	Shader shader;
	shader.id = id;

	return shader;
}
