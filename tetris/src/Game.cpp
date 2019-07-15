#include "Game.h"
#include "Shader.h"
#include "Figure.h"
#include "GLFigure.h"
#include "GLBlock.h"
#include "GLFrame.h"

static Game* instance;

Game& GetGameInstance() {
	if (nullptr == instance) {
		instance = new Game();
	};
	return *instance;
}

Game::Game():
	score(0),
	m_block_sz(20),
	m_sz_x_blocks(32),
	m_sz_y_blocks(24),
	size_px_x(m_sz_x_blocks * m_block_sz),
	size_px_y(m_sz_y_blocks * m_block_sz),
	m_fld_blk_x(10),
	m_fld_blk_y(20),
	m_fld_sz_x(m_block_sz * m_fld_blk_x),
	m_fld_sz_y(m_block_sz * m_fld_blk_y),
	current_tic(0),
	advance_velocity(0),
	advance_tic(0),
	wnd(nullptr),
	fld(nullptr),
	current_fig(nullptr),
	next_fig(nullptr),
	program(nullptr),
	pProgramFrame(nullptr),
	m_textures(m_color_count),
	m_model(1.0f),
	m_view(1.0f)
{
	m_model = glm::scale(m_model, glm::vec3(m_block_sz, m_block_sz, m_block_sz));
	m_view = glm::translate(m_view, glm::vec3(-1.0f, 1.0f, 0.0f));
	m_view = glm::scale(m_view, glm::vec3(2.0f / m_fld_sz_x, -2.0f / m_fld_sz_y, 1.0f));
}

void Game::wnd_key_callback(GLFWwindow* pWnd, int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS == action || GLFW_REPEAT == action) {
		GetGameInstance().process_input(key);
	}
}

int Game::load_resources()
{
	char sFileName[256] = { 0 };
	for (int i = 0; i < m_color_count; ++i)
	{
		snprintf(sFileName, 256, "resources\\tile_%d.png", i);
		std::cout << "Loading texture " << sFileName << std::endl;
		m_textures[i] = new GLTexture;
		if (false == m_textures[i]->LoadTexture(sFileName))
			return 1;
		m_textures[i]->SetCoords({ 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 
									1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f });
		if (m_textures[i]->LoadToGL())
			return 2;
		std::cout << "Loaded texture" << std::endl;
	}
	GetBlockInstance().SetTextureCoords(*m_textures[0]);
	GetBlockInstance().LoadToGL();

	GetFrameObject().LoadToGL();

	Shader* vertex_sh = LoadShaderFromFile(SH_T_VERTEX, "shaders\\block_mat.vert", {"model", "view"});
	Shader* fragment_sh = LoadShaderFromFile(SH_T_FRAGMENT, "shaders\\block.frag", { });
	program = new Program(*vertex_sh, *fragment_sh);
	if (program->Link()) {
		std::cout << "Unable to link block shader program\n";
		return 3;
	}
	program->CleanupShaders();
	delete vertex_sh;
	delete fragment_sh;

	program->Use();
	GLint v_loc = program->GetUniformLocation("view");
	glUniformMatrix4fv(v_loc, 1, GL_FALSE, glm::value_ptr(m_view));


	Shader* frameVertShader = LoadShaderFromFile(SH_T_VERTEX, "shaders\\frame.vert", {});
	Shader* frameFragShader = LoadShaderFromFile(SH_T_FRAGMENT, "shaders\\frame.frag", { "aColor" });
	pProgramFrame = new Program(*frameVertShader, *frameFragShader);
	if (pProgramFrame->Link()) {
		std::cout << "Unable to link frame shader program\n";
		return 4;
	}
	pProgramFrame->CleanupShaders();
	pProgramFrame->Use();
	GLint col_loc = pProgramFrame->GetUniformLocation("aColor");
	glUniform3f(col_loc, 1.0f, 1.0f, 1.0f);
	delete frameVertShader;
	delete frameFragShader;
	return 0;
}

int Game::init_window() {
	// initializing GLFW window
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
	return 0;
}

void Game::use_color(unsigned col)
{
	m_textures[col - 1]->Use();
}

int Game::initialize()
{
	if (init_window())
		return 1;
	if (load_resources())
		return 2;
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSetKeyCallback(wnd, wnd_key_callback);
	auto seed = glfwGetTimerValue();
	std::srand(seed);
	std::cout << "Initialized with seed " << seed << std::endl;

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
		current_color = next_color;
		fld->set_current_color(current_color);
		next_color = generate_color();
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
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(m_block_sz, m_block_sz, m_fld_sz_x, m_fld_sz_y);
	pProgramFrame->Use();
	GetFrameObject().Render();
	program->Use();
	GLint c_loc = program->GetUniformLocation("model");
	
	glm::mat4 model(1.0f);

	for (int y = 3; y < fld->get_size_y(); ++y)
		for (int x = 0; x < fld->get_size_x(); ++x)
			if (fld->get_value(x, y) != 0)
			{
				model = m_model * glm::translate(glm::mat4(1.0f), glm::vec3(x, y - 3, 0));
				glUniformMatrix4fv(c_loc, 1, GL_FALSE, glm::value_ptr(model));
				if (fld->get_value(x, y) != 9) 
				{
					use_color(fld->get_value(x, y));
				}
				else
				{
					use_color(current_color);
				}
				GetBlockInstance().Render();
			}
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

unsigned int Game::generate_color()
{
	return std::rand() % m_color_count + 1;
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
	current_color = generate_color();
	next_fig = generate_figure();
	next_color = generate_color();
	fld->set_current_figure(current_fig, 4, 0);
	fld->set_current_color(current_color);
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

