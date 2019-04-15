#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

class Field;

enum ENTFigureType {
	FIG_SQUARE,
	FIG_LINE,
	FIG_Z,
	FIG_REV_Z,
	FIG_R,
	FIG_REV_R,
	FIG_T,
	FIG_COUNT
};

struct STFigurePos {
	int size_y;
	int size_x;
	const int layout[4][4];
};

typedef std::vector<STFigurePos*> VTFigurePos;
typedef VTFigurePos::const_iterator VTFigurePosIt;

class CFigure {
	int pos_x;
	int pos_y;
	ENTFigureType tp;
	const VTFigurePos& positions;
	VTFigurePosIt cur_pos;
	Field* fld;
public:
	CFigure(ENTFigureType fig_type, int pos_num, Field* fld);

	VTFigurePosIt next_pos();

	VTFigurePosIt prev_pos();

	VTFigurePosIt get_pos();

	int get_pos_x();
	int get_pos_y();
	void set_pos_x(int x);
	void set_pos_y(int y);

	void print_pos();
};

const std::string& fig_type_to_str(ENTFigureType tp);
int load_positions();
void print_positions();


