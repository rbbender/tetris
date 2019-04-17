#pragma once
#include <vector>
#include "Figure.h"

typedef std::vector<int> Row;

enum STEP_RESULT {
	SR_OK,
	SR_LANDED,
	SR_GAME_OVER
};

class Field {
	const int VIS_Y = 3;
	const int SZ_X;
	const int SZ_Y;
	int cur_pos_x;
	int cur_pos_y;
	std::vector<Row> field;
	CFigure* cur_figure;
	typedef std::vector<Row>::iterator y_itr;
	bool is_position_possible(const STFigurePos& ps, int p_x, int p_y);
	bool test_landed(int p_x, int p_y);
public:
	Field(int size_x = 10, int size_y = 20);
	void dbg_print();
	int set_current_figure(CFigure* fig, int pos_x, int pos_y);
	int remove_current_figure();
	int merge_current_figure();
	bool can_move_right();
	bool can_move_left();
	bool can_rotate_cw();
	bool can_rotate_ccw();
	bool is_landed();
	bool is_game_over();
	int force_land();
	int move_right();
	int move_left();
	int rotate_cw();
	int rotate_ccw();

	// main method
	STEP_RESULT make_step();
};
