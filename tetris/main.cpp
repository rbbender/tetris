#include <iostream>
#include "Figure.h"
#include "Field.h"

Field* fld;

void print_dbg() {
	std::cout << "-------------------------------\n";
	fld->dbg_print();
	std::cout << "-------------------------------\n";
	std::cout << "Can move left? ---> " << fld->can_move_left() << std::endl;
	std::cout << "Can move right? ---> " << fld->can_move_right() << std::endl;
	std::cout << "Is landed? ---> " << fld->is_landed() << std::endl;
}

int main() {
	load_positions();
	print_positions();

	fld = new Field;

	CFigure fig(FIG_R, 0, fld);
	fld->set_current_figure(&fig, 7, 5);
	print_dbg();
	fld->move_right();
	print_dbg();
	fld->move_left();
	print_dbg();
	fld->move_left();
	print_dbg();
	fld->move_left();
	print_dbg();
	fld->move_left();
	print_dbg();
	fld->rotate_cw();
	print_dbg();
	fld->rotate_cw();
	print_dbg();
	fld->rotate_cw();
	print_dbg();
	fld->rotate_cw();
	print_dbg();
	fld->rotate_ccw();
	print_dbg();
	fld->rotate_ccw();
	print_dbg();
	fld->rotate_ccw();
	print_dbg();
	fld->rotate_ccw();
	print_dbg();

	getchar();
}