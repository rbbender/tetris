#include <iostream>
#include "StaticScreen.h"
#include "Program.h"

static int block[] = { 0, 0,
						20, 0,
						20, 20,
						20, 20,
						0, 20,
						0, 0 };

StaticScreen::StaticScreen()
{

}

void StaticScreen::key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(wnd, GLFW_TRUE);
}

void StaticScreen::draw()
{
	if (!glfwInit()) {
		std::cout << "Unable to init glfw\n";
		return;
	}

	GLFWwindow* wnd = glfwCreateWindow(640, 480, "Static Screen", nullptr, nullptr);
	if (!wnd) {
		std::cout << "Unable to create GLFW window\n";
		glfwTerminate();
		return;
	}
	glfwSetKeyCallback(wnd, key_callback);
	glfwMakeContextCurrent(wnd);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to init GLAD\n";
		glfwTerminate();
		return;
	}
	Shader* pVertShader = LoadShaderFromFile(SH_T_VERTEX, "simple.vert", {});
	Shader* pFragShader = LoadShaderFromFile(SH_T_FRAGMENT, "simple.frag", {});
	Program* pProgram = new Program(*pVertShader, *pFragShader);
	pProgram->Link();
	pProgram->CleanupShaders();

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(block), block, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, (void*)0);

	while (!glfwWindowShouldClose(wnd)) {
		pProgram->Use();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}
}


StaticScreen::~StaticScreen()
{
}
