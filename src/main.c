#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader.h"

#define MAX_MODE 3

static const GLfloat VERTICES[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

static const GLuint INDICES[] = {
	0, 1, 2
};

static const GLfloat SCALE_MATRIX[] = {
	0.5f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.0f, 0.0f, 0.5f
};

static const GLfloat ROTATION_MATRIX[] = {
	0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

static const GLfloat TRANSLATION_MATRIX[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f
};

static int mode = 0;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (mode == MAX_MODE) {
			mode = 0;
		} else {
			mode++;
		}
	}
}

int main(void) {
	if (glfwInit() != GLFW_TRUE) {
		fprintf(stderr, "Error: glfw failed to init\n");
		return 1;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Raw GFX", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Error: Failed to create window\n");
		return 1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((void *(*)(const char *)) glfwGetProcAddress);

	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

	Shader default_shader = load_shader("src/shaders/default.vert", "src/shaders/default.frag");
	Shader mult_shader = load_shader("src/shaders/mult.vert", "src/shaders/mult.frag");
	Shader translate_shader = load_shader("src/shaders/translate.vert", "src/shaders/translate.frag");

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLuint mult_location = glGetUniformLocation(mult_shader.id, "mult");
		GLuint translate_location = glGetUniformLocation(translate_shader.id, "translate");

		switch (mode) {
			case 0:
				glUseProgram(default_shader.id);
				break;
			case 1:
				glUseProgram(mult_shader.id);
				glUniformMatrix3fv(mult_location, 1, GL_FALSE, SCALE_MATRIX);
				break;
			case 2:
				glUseProgram(mult_shader.id);
				glUniformMatrix3fv(mult_location, 1, GL_FALSE, ROTATION_MATRIX);
				break;
			case 3:
				glUseProgram(translate_shader.id);
				glUniformMatrix4fv(translate_location, 1, GL_FALSE, TRANSLATION_MATRIX);
				break;
		}

		glDrawElements(GL_TRIANGLES, sizeof(INDICES) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
