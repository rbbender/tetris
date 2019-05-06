#pragma once
#include <vector>
#include "Figure.h"
#include "IField.h"

typedef std::vector<int> Row;

class Field : public IField {
	const int VIS_Y = 3;
	const int SZ_X;
	const int SZ_Y;
	int cur_pos_x;
	int cur_pos_y;
	bool to_redraw;
	std::vector<Row> field;
	CFigure* cur_figure;
	typedef std::vector<Row>::iterator y_itr;
	bool is_position_possible(const STFigurePos& ps, int p_x, int p_y);
	bool test_landed(int p_x, int p_y);
	bool can_move_right();
	bool can_move_left();
	bool can_rotate_cw();
	bool can_rotate_ccw();
	int remove_current_figure();
	int merge_current_figure(int col=9);
	bool is_row_complete(int i);
	int delete_row(int i);
	int on_figure_landed();
	bool is_landed();
	bool is_game_over();
	void set_redraw_required();
public:
	Field(int size_x = 10, int size_y = 20);
	void dbg_print();
	int set_current_figure(CFigure* fig, int pos_x, int pos_y);
	int force_land();
	int move_right();
	int move_left();
	int rotate_cw();
	int rotate_ccw();
	int get_size_x();
	int get_size_y();
	int get_value(int x, int y);
	bool is_redraw_required();
	void redraw_completed();

	// main "tic" method
	void make_step();
	STEP_RESULT step_result(int& lines);
};
