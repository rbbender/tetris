#include <iostream>
#include "Figure.h"
#include "Field.h"
#include "Game.h"
#include "StaticScreen.h"


int main() {
	load_positions();
	print_positions();
	//StaticScreen scr;
	//scr.draw();
	if (GetGameInstance().initialize() != 0) {
		std::cout << "Error initializing game\n";
		getchar();
		return 1;
	}
	GetGameInstance().start_game();
	GetGameInstance().main_loop();
	//getchar();
/*	CFigure fig(FIG_R, 0, fld);
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
	fld->force_land();
	print_dbg(); */
}