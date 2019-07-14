#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class StaticScreen
{
public:
	StaticScreen();
	static void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods);
	void draw();
	~StaticScreen();
};

