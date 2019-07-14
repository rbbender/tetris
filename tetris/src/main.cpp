#include <iostream>
#include "Figure.h"
#include "Field.h"
#include "Game.h"
#include "StaticScreen.h"

int InitGLFW() {
	if (GLFW_FALSE == glfwInit()) {
		std::cout << "ERROR: unable to initialize GLFW\n";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	std::cout << "Initialized GLFW\n";
	return 0;
}

int main() {
	if (InitGLFW())
		return 2;
	if (GetGameInstance().initialize()) {
		std::cout << "Error initializing game\n";
		return 1;
	}
	load_positions();
	//print_positions();
	//GetGameInstance().initialize();
	GetGameInstance().start_game();
	GetGameInstance().main_loop();
}