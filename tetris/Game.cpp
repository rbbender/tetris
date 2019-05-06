#include "Game.h"
#include "Shader.h"
#include <vec3.hpp>
#include <mat3x3.hpp>

static Game* instance;

const int BLK_SZ = 20;

static int block[] = {0,	  0,
					  BLK_SZ, 0,
					  0,	  BLK_SZ,
					  BLK_SZ, 0,
					  BLK_SZ, BLK_SZ,
					  0,	  BLK_SZ};

Game& GetGameInstance() {
	if (nullptr == instance) {
		instance = new Game();
	};
	return *instance;
}

Game::Game():
	score(0),
	size_px_x(DEF_SZ_X),
	size_px_y(DEF_SZ_Y),
	current_tic(0),
	advance_velocity(0),
	advance_tic(0),
	wnd(nullptr),
	fld(nullptr),
	current_fig(nullptr),
	next_fig(nullptr)
{
}

void Game::wnd_key_callback(GLFWwindow* pWnd, int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS == action) {
		GetGameInstance().process_input(key);
	}
}

int Game::initialize(int sz_px_x, int sz_px_y)
{
	// initializing GLFW window
	if (!glfwInit()) {
		std::cout << "ERROR: unable to initialize GLFW\n";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	wnd = glfwCreateWindow(size_px_x, size_px_y, "MegaTetris", nullptr, nullptr);
	if (!wnd) {
		glfwTerminate();
		std::cout << "ERROR: unable to create GLFW window\n";
		return -2;
	}
	glfwMakeContextCurrent(wnd);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to init GLAD" << std::endl;
		glfwTerminate();
		return -3;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSetKeyCallback(wnd, wnd_key_callback);
	auto seed = glfwGetTimerValue();
	std::srand(seed);
	std::cout << "Initialized with seed " << seed << std::endl;
	Shader* vertex_sh = LoadShaderFromFile(SH_T_VERTEX, "vertex.txt", {"simple_c"});
	Shader* fragment_sh = LoadShaderFromFile(SH_T_FRAGMENT, "fragment.txt", { "color" });
	program = new Program(*vertex_sh, *fragment_sh);
	if (program->Link()) {
		std::cout << "Unable to link shader program\n";
		return -4;
	}
	program->CleanupShaders();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(block), block, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, (void*)0);
	return 0;
}

void Game::process_input(int key)
{
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(wnd, GLFW_TRUE);
		break;
	}
	if (!fld)
		return;
	switch (key) {
	case GLFW_KEY_LEFT:
		fld->move_left();
		break;
	case GLFW_KEY_RIGHT:
		fld->move_right();
		break;
	case GLFW_KEY_UP:
		fld->rotate_cw();
		break;
	case GLFW_KEY_DOWN:
		fld->rotate_ccw();
		break;
	case GLFW_KEY_SPACE:
		fld->force_land();
		break;
	}
}

void Game::update_state()
{
	if (!fld)
		return;
	int lines;
	STEP_RESULT res = fld->step_result(lines);
	score += lines;
	int diff = current_tic - advance_tic;
	//std::cout << "res: " << res << "\tdiff: " << diff << std::endl;
	switch (res) {
	case SR_OK:
		if (diff >= 0) {
			fld->make_step();
			advance_tic = current_tic + advance_velocity - diff;
		}
		break;
	case SR_LANDED:
		fld->set_current_figure(next_fig, 4, 0);
		delete current_fig;
		current_fig = next_fig;
		next_fig = generate_figure();
		advance_tic = current_tic + advance_velocity - diff;
		break;
	case SR_GAME_OVER:
		std::cout << "Score: " << score << std::endl;
		stop_game();
		delete next_fig;
		delete current_fig;
		break;
	}
}

void Game::redraw()
{
	glViewport(0, 0, 640, 480);
	glClear(GL_COLOR_BUFFER_BIT);
	program->Use();
	glBindVertexArray(VAO);
	GLint col_loc = program->GetUniformLocation("color");
	GLint c_loc = program->GetUniformLocation("simple_c");
	glUniform3f(col_loc, 1.0f, 1.0f, 1.0f);
	//if (fld->is_redraw_required()) {
	for (int y = 3; y < fld->get_size_y(); ++y)
		for (int x = 0; x < fld->get_size_x(); ++x)
			if (fld->get_value(x, y) != 0) {
				glUniform2i(c_loc, x, y);
				glDrawArrays(GL_TRIANGLES, 0, 6);
		}


		//fld->redraw_completed();
	//}
	glfwSwapBuffers(wnd);
}

int Game::main_loop()
{
	double delta_time, cur_time;
	double tic_time;
	while (!glfwWindowShouldClose(wnd)) {
		cur_time = glfwGetTime();
		tic_time = cur_time + TIC_TIME;
		glfwPollEvents();
		update_state();
		redraw();
		delta_time = tic_time - glfwGetTime();
		current_tic = cur_time / TIC_TIME;
		//std::cout << "cur_time=" << cur_time << "\ttic_time=" << tic_time << "\tdelta_time=" << delta_time << std::endl;
		if (delta_time > 0.0) {
			Sleep(delta_time);
		}
		else if (delta_time < 0.0) {
			unsigned missed_tic = ((unsigned)(-delta_time / TIC_TIME));
			std::cout << "Missed tics: " << missed_tic << std::endl;
		}
	}
	return 0;
}

CFigure* Game::generate_figure()
{
	ENTFigureType tp = (ENTFigureType) (std::rand() % get_figure_count());
	unsigned pos = std::rand() % get_figure_pos_count(tp);
	return new CFigure(tp, pos);
}

void Game::start_game()
{
	if (fld)
		stop_game();
	fld = new Field();
	current_tic = 0;
	advance_tic = (unsigned)FPS;
	advance_velocity = (unsigned)FPS;
	current_fig = generate_figure();
	next_fig = generate_figure();
	fld->set_current_figure(current_fig, 4, 0);
}

void Game::stop_game()
{
	if (fld)
		delete fld;
	fld = nullptr;
}


Game::~Game()
{
	if (wnd)
		glfwDestroyWindow(wnd);
	glfwTerminate();
}
