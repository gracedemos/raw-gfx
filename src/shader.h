#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct Shader {
	GLuint id;
} Shader;

Shader load_shader(const char *vert_path, const char *frag_path);

#endif
