#pragma once
#include <vector>
#include "Figure.h"

typedef std::vector<int> Row;

class Field {
	const int VIS_Y = 3;
	const int SZ_X;
	const int SZ_Y;
	std::vector<Row> field;
	CFigure* cur_figure;
	typedef std::vector<Row>::iterator y_itr;
public:
	Field(int size_x = 10, int size_y = 20);
	void dbg_print();
	int set_current_figure(CFigure* fig);
	int remove_current_figure();
	int merge_current_figure();
};
