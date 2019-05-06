#pragma once
enum STEP_RESULT {
	SR_OK,
	SR_LANDED,
	SR_GAME_OVER
};

class CFigure;
class IField
{
public:
	virtual void dbg_print()=0;
	virtual int set_current_figure(CFigure* fig, int pos_x, int pos_y)=0;
	virtual int force_land()=0;
	virtual int move_right()=0;
	virtual int move_left()=0;
	virtual int rotate_cw()=0;
	virtual int rotate_ccw()=0;
	virtual void make_step()=0;
	virtual STEP_RESULT step_result(int& lines)=0;
	virtual bool is_redraw_required()=0;
	virtual void redraw_completed() = 0;
};

