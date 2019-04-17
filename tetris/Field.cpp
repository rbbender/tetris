#include <iostream>
#include "Field.h"


bool Field::is_position_possible(const STFigurePos& ps, int p_x, int p_y)
{
	if (p_x < 0 || p_y < 0 ||
		p_x + ps.size_x >= SZ_X ||
		p_y + ps.size_y >= SZ_Y)
		return false;
	for (int i = 0; i < ps.size_y; ++i)
		for (int k = 0; k < ps.size_x; ++k)
			if (field[p_y + i][p_x + k] > 0 &&
				field[p_y + i][p_x + k] != 9 &&
				ps.layout[i][k] == 1)
				return false;
	return true;
	return false;
}

Field::Field(int size_x, int size_y) :
	SZ_X(size_x), 
	SZ_Y(size_y + VIS_Y),
	cur_pos_x(0),
	cur_pos_y(0),
	cur_figure(nullptr)
{
	std::cout << "Initializing field: " << size_y << "x" << size_x << std::endl;
	field = std::vector<Row>(SZ_Y, Row(SZ_X, 0));
	std::cout << "Initialized\n";
};

void Field::dbg_print() 
{
	for (int i = VIS_Y; i < SZ_Y; ++i) {
		for (int k = 0; k < SZ_X; ++k)
			std::cout << field[i][k];
		std::cout << std::endl;
	}
}

int Field::merge_current_figure() {
	if (cur_figure == nullptr)
		return 0;
	const VTFigurePosIt cur_pos = cur_figure->get_pos();
	int sz_x = (*cur_pos)->size_x;
	int sz_y = (*cur_pos)->size_y;
	for (int i = cur_pos_y; i < cur_pos_y + sz_y; ++i)
		for (int k = cur_pos_x; k < cur_pos_x + sz_x; ++k)
			if ((*cur_pos)->layout[i - cur_pos_y][k - cur_pos_x] == 1)
				field[i][k] = 9;
	return 0;
}

bool Field::can_move_right()
{
	if (nullptr == cur_figure)
		return false;
	STFigurePos* cur_pos = *(cur_figure->get_pos());
	for (int i = 0; i < cur_pos->size_y; ++i) {
		int candidate_x = cur_pos_x + cur_pos->right_border[i] + 1;
		if ((candidate_x >= SZ_X) || (field[cur_pos_y + i][candidate_x] == 1))
			return false;
	}
	return true;
}

bool Field::can_move_left()
{	
	if (nullptr == cur_figure)
		return false;
	STFigurePos* cur_pos = *(cur_figure->get_pos());
	for (int i = 0; i < cur_pos->size_y; ++i) {
		int candidate_x = cur_pos_x + cur_pos->left_border[i] - 1;
		if ((candidate_x < 0) || (field[cur_pos_y + i][candidate_x] == 1))
			return false;
	}
	return true;

	return false;
}

bool Field::can_rotate_cw()
{
	if (nullptr == cur_figure)
		return false;
	const STFigurePos* nxt = *(cur_figure->peek_next_pos());
	return is_position_possible(*nxt, cur_pos_x, cur_pos_y);
}

bool Field::can_rotate_ccw()
{
	if (nullptr == cur_figure)
		return false;
	const STFigurePos* nxt = *(cur_figure->peek_prev_pos());
	return is_position_possible(*nxt, cur_pos_x, cur_pos_y);
}

bool Field::is_landed()
{
	return test_landed(cur_pos_x, cur_pos_y);
}

bool Field::test_landed(int p_x, int p_y)
{
	if (nullptr == cur_figure)
		return false;
	VTFigurePosIt cur_pos = cur_figure->get_pos();
	for (int k = 0; k < (*cur_pos)->size_x; ++k) {
		int candidate_y = p_y + (*cur_pos)->bottom_border[k] + 1;
		if (candidate_y >= SZ_Y) return true;
		if ((field[candidate_y][p_x + k] > 0) &&
			(field[candidate_y][p_x + k] != 9))
			return true;
	}
	return false;
}

bool Field::is_game_over()
{
	if (is_landed() &&
		cur_pos_y < VIS_Y)
		return true;
	return false;
}


int Field::remove_current_figure() {
	if (cur_figure == nullptr)
		return 0;
	const VTFigurePosIt cur_pos = cur_figure->get_pos();
	int sz_x = (*cur_pos)->size_x;
	int sz_y = (*cur_pos)->size_y;
	for (int i = cur_pos_y; i < cur_pos_y + sz_y; ++i)
		for (int k = cur_pos_x; k < cur_pos_x + sz_x; ++k)
			if ((*cur_pos)->layout[i - cur_pos_y][k - cur_pos_x] == 1 &&
				field[i][k] == 9)
				field[i][k] = 0;
	return 0;
}

int Field::set_current_figure(CFigure* fig, int pos_x, int pos_y) {
	remove_current_figure();
	cur_figure = fig;
	cur_pos_x = pos_x;
	cur_pos_y = pos_y;
	merge_current_figure();
	return 0;
}

int Field::force_land()
{
	if (nullptr == cur_figure)
		return 1;
	int i = cur_pos_y;
	for (; i < SZ_Y && !test_landed(cur_pos_x, i); ++i)
		;
	remove_current_figure();
	cur_pos_y = i;
	merge_current_figure();
	return 0;
}

int Field::move_right()
{
	if (!can_move_right())
		return 1;
	remove_current_figure();
	++cur_pos_x;
	merge_current_figure();
	return 0;
}

int Field::move_left()
{
	if (!can_move_left())
		return 1;
	remove_current_figure();
	--cur_pos_x;
	merge_current_figure();
	return 0;
}

int Field::rotate_cw()
{
	if (!can_rotate_cw()) {
		return 1;
	}
	remove_current_figure();
	cur_figure->next_pos();
	merge_current_figure();
	return 0;
}

int Field::rotate_ccw()
{
	if (!can_rotate_ccw())
		return 1;
	remove_current_figure();
	cur_figure->prev_pos();
	merge_current_figure();
	return 0;
}
