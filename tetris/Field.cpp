#include <iostream>
#include "Field.h"


Field::Field(int size_x, int size_y) : 
	SZ_X(size_x), 
	SZ_Y(size_y + VIS_Y),
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
	int p_x = cur_figure->get_pos_x();
	int p_y = cur_figure->get_pos_y();
	int sz_x = (*cur_pos)->size_x;
	int sz_y = (*cur_pos)->size_y;
	for (int i = p_y; i < p_y + sz_y; ++i)
		for (int k = p_x; k < p_x + sz_x; ++k)
			if ((*cur_pos)->layout[i - p_y][k - p_x] == 1)
				field[i][k] = 1;
	return 0;
}


int Field::remove_current_figure() {
	if (cur_figure == nullptr)
		return 0;
	const VTFigurePosIt cur_pos = cur_figure->get_pos();
	int p_x = cur_figure->get_pos_x();
	int p_y = cur_figure->get_pos_y();
	int sz_x = (*cur_pos)->size_x;
	int sz_y = (*cur_pos)->size_y;
	for (int i = p_y; i < p_y + sz_y; ++i)
		for (int k = p_x; k < p_x + sz_x; ++k)
			if ((*cur_pos)->layout[i - p_y][k - p_x] == 1 &&
				field[i][k] == 1)
				field[i][k] = 0;
	return 0;
}

int Field::set_current_figure(CFigure* fig) {
	remove_current_figure();
	cur_figure = fig;
	merge_current_figure();
	return 0;
}
