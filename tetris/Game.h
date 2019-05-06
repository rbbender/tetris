#pragma once
#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Field.h"
#include "Figure.h"
#include "Program.h"

class Game
{
	const static int DEF_SZ_X = 640;
	const static int DEF_SZ_Y = 480;
	const double FPS = 30.0;
	const double TIC_TIME = (double) 1.0 / FPS;
	int score;
	int size_px_x;
	int size_px_y;
	unsigned long current_tic;
	unsigned long advance_tic;
	unsigned advance_velocity;
	unsigned VAO;
	unsigned VBO;
	GLFWwindow* wnd;
	Field* fld;
	CFigure* current_fig;
	CFigure* next_fig;
	Program* program;
public:
	Game();
	static void wnd_key_callback(GLFWwindow* pWnd, int key, int scancode, int action, int mods);
	int initialize(int sz_px_x=DEF_SZ_X, int sz_px_y=DEF_SZ_Y);
	void process_input(int key);
	void update_state();
	void redraw();
	int main_loop();
	CFigure* generate_figure();
	void start_game();
	void stop_game();
	~Game();
};

Game& GetGameInstance();

