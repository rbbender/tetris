#pragma once
#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLTexture.h>
#include "Field.h"
#include "Figure.h"
#include "Program.h"
#include <mat4x4.hpp>

class Game
{
	typedef std::vector<GLTexture*> VTextures;
	const unsigned int m_color_count = 8;
	const double FPS = 30.0;
	const double TIC_TIME = (double) 1.0 / FPS;
	int score;
	unsigned m_block_sz;
	unsigned m_sz_x_blocks;
	unsigned m_sz_y_blocks;
	unsigned size_px_x;
	unsigned size_px_y;
	unsigned long current_tic;
	unsigned long advance_tic;
	unsigned advance_velocity;
	unsigned VAO[2];
	unsigned VBO[2];
	GLFWwindow* wnd;
	Field* fld;
	CFigure* current_fig;
	unsigned int current_color;
	CFigure* next_fig;
	unsigned int next_color;
	Program* program;
	Program* pProgramFrame;
	VTextures m_textures;
	glm::mat4 m_mat_scale;
	glm::mat4 m_mat_block;

public:
	Game();
	static void wnd_key_callback(GLFWwindow* pWnd, int key, int scancode, int action, int mods);
	int initialize();
	void process_input(int key);
	void update_state();
	void redraw();
	int main_loop();
	CFigure* generate_figure();
	unsigned int generate_color();
	void start_game();
	void stop_game();
	~Game();
private:
	int load_resources();
	int init_window();
	void use_color(unsigned col);
	void set_block_size(unsigned sz_px);
	unsigned get_block_size();

};

Game& GetGameInstance();

