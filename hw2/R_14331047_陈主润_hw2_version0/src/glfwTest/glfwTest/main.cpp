// glfwTest.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"

// glew
#define GLEW_STATIC
#include <GL/glew.h>
// glfw

#include <iostream>
#include <GLFW\glfw3.h>

#include <iostream>
#include "Shader.hpp"

//source codes
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 myColor;\n"
"void main() {\n"
"gl_Position = vec4(position, 1.0);\n"
"myColor = color;\n"
"}";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 myColor;\n"
"out vec4 color;\n"
"void main() {\n"
"color = vec4(myColor, 1.0f);\n"
"}";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, const char * argv[]) {
	// --init--
	//set up GLFW
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	GLFWwindow* window = glfwCreateWindow(640, 480, "HelloTriangle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// set up GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization error!" << std::endl;
		return -1;
	}

	std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// set viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	//--stop initialization--

	//build shader program
	Shader myShader(vertexShaderSource, fragmentShaderSource);

	//set vertices of four triangles(as four mountains)
	GLfloat triangle_points[] = {
		//set the vertices to red, green and blue as colorful mountain
		-0.5f, 0.8f, 0.0f,
		-0.75f, 0.3f, 0.0f,
		-0.25f, 0.3f, 0.0f,
		//common mountains
		0.1f,  0.6f, 0.0f,
		0.3f,  0.0f, 0.0f,
		-0.1f, 0.0f, 0.0f,

		0.4f, 0.8f, 0.0f,
		0.8f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.7f, 0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.4f, 0.0f, 0.0f
	};
	//vertices color for each mountain
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f,

		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f,

		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f,
		0.5f, 0.3f, 0.1f
	};
	GLuint mountain_indices[] = {
		0, 1, 2,    //colorful mountain
		3, 4, 5, //common mountain
		6, 7, 8,
		9, 10, 11
	};

	//line points
	GLfloat line_points[] = {
		//points(3)         //colors(3)
		-0.5f, -0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.3f, -0.4f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.8f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.2f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,

		-0.8f, -0.6f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.4f, -0.6f, 0.0f, 1.0f, 1.0f, 1.0f,

		-0.6f, -0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f,  -0.9f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.3f,  -0.7f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.9f,  -0.7f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.1f,  -0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  -0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
	};
	GLuint line_indices[] = {
		0, 1,
		2, 3,
		4, 5,
		6, 7,
		8, 9
	};

	// draw rectangle with two triangle
	GLfloat rectangle_points[] = {
		//points(3)          //colors(3)
		-1.0f, -0.3f, 0.0f,  0.0f, 0.8f, 1.0f,
		1.0f,  -0.3f, 0.0f,  0.0f, 0.8f, 1.0f,
		1.0f,  -1.0f, 0.0f,  0.0f, 0.8f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.8f, 1.0f
	};
	GLuint river_indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// point
	GLfloat points[] = {
		-0.8f, 0.2f, 0.0f, 0.7f, 0.7f, 0.7f,
		-0.6f, 0.2f, 0.0f, 0.7f, 0.7f, 0.7f,
		-0.4f, 0.2f, 0.0f, 0.7f, 0.7f, 0.7f,
		-0.2f, 0.2f, 0.0f, 0.7f, 0.7f, 0.7f
	};
	 


	//draw two triangles as mountains
	//create VAO and VBO
	GLuint points_VBO, colors_VBO, triangles_VAO, mountain_EBO;
	glGenVertexArrays(1, &triangles_VAO);
	glGenBuffers(1, &points_VBO);
	glGenBuffers(1, &colors_VBO);
	glGenBuffers(1, &mountain_EBO);
	glBindVertexArray(triangles_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_points), triangle_points, GL_STATIC_DRAW);
	//bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mountain_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mountain_indices), mountain_indices, GL_STATIC_DRAW);
	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//enable array buffer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//unable array VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//draw a rectangle as rivers
	//rectangle
	GLuint rectangle_VAO, rectangle_VBO, river_EBO;
	glGenVertexArrays(1, &rectangle_VAO);
	glGenBuffers(1, &rectangle_VBO);
	glGenBuffers(1, &river_EBO);
	glBindVertexArray(rectangle_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_points), rectangle_points, GL_STATIC_DRAW);
	//bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, river_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(river_indices), river_indices, GL_STATIC_DRAW);
	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//enable array buffer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//unable array VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//lines
	GLuint lines_VAO, lines_VBO, lines_EBO;
	glGenVertexArrays(1, &lines_VAO);
	glGenBuffers(1, &lines_VBO);
	glGenBuffers(1, &lines_EBO);
	glBindVertexArray(lines_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, lines_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_points), line_points, GL_STATIC_DRAW);
	//bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_indices), line_indices, GL_STATIC_DRAW);
	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//enable array buffer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//unable array VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//points
	GLuint sun_VBO, sun_VAO;
	glGenVertexArrays(1, &sun_VAO);
	glGenBuffers(1, &sun_VBO);
	glBindVertexArray(sun_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sun_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//unable VAO VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//set keycallback
	glfwSetKeyCallback(window, key_callback);

	// drawing loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		// draw triangles by shader program
		myShader.Use();
		//draw mountains
		glBindVertexArray(triangles_VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//draw river
		glBindVertexArray(rectangle_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//decorate the river with lines
		glBindVertexArray(lines_VAO);
		glDrawElements(GL_LINES, 10, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//draw sun
		glBindVertexArray(sun_VAO);
		glPointSize(10.0f);
		glDrawArrays(GL_POINTS, 0, 4);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &points_VBO);
	glDeleteBuffers(1, &colors_VBO);
	glDeleteBuffers(1, &lines_VBO);
	glDeleteBuffers(1, &rectangle_VBO);
	glDeleteBuffers(1, &sun_VBO);
	glDeleteBuffers(1, &mountain_EBO);
	glDeleteBuffers(1, &river_EBO);
	glDeleteBuffers(1, &lines_EBO);
	glfwTerminate();

	return 0;
}

