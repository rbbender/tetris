#include "Figure.h"
#include "Field.h"

static std::vector<VTFigurePos> FIG_POSITIONS(FIG_COUNT);

static std::vector<std::string> FIG_TYPE_STR = { "SQUARE", "LINE", "Z", "REV_Z", "R", "REV_R", "T" };

CFigure::CFigure(ENTFigureType fig_type, int pos_num) :
		tp(fig_type),
		positions(FIG_POSITIONS[fig_type]),
		cur_pos(positions.cbegin() + pos_num)
	{};

VTFigurePosIt CFigure::next_pos() {
	++cur_pos;
	if (cur_pos == positions.cend())
		cur_pos = positions.cbegin();
	return cur_pos;
};

VTFigurePosIt CFigure::prev_pos() {
	if (cur_pos == positions.cbegin())
		cur_pos = positions.cend();
	return --cur_pos;
};

VTFigurePosIt CFigure::get_pos() {
	return cur_pos;
}

VTFigurePosIt CFigure::peek_next_pos()
{
	if (cur_pos + 1 == positions.cend())
		return positions.cbegin();
	return cur_pos + 1;
}

VTFigurePosIt CFigure::peek_prev_pos()
{
	if (cur_pos == positions.cbegin())
		return positions.cend() - 1;
	return cur_pos - 1;
}

void CFigure::print_pos() {
	for (int i = 0; i < (*cur_pos)->size_x; ++i) {
		for (int k = 0; k < (*cur_pos)->size_y; ++k)
			if ((*cur_pos)->layout[i][k] == 1)
				std::cout << "1";
			else
				std::cout << " ";
		std::cout << std::endl;
	}
};

static STFigurePos FIG_POS_SQUARE[] = { {2, 2, 
								{{1, 1, 0, 0},
								 {1, 1, 0, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{1, 1, 0, 0},
								{1, 1, 0, 0},
								}};

static STFigurePos FIG_POS_LINE[] = { {1, 4,
								{{1, 1, 1, 1},
 								 {0, 0, 0, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{3, 0, 0, 0},
								{0, 0, 0, 0},
								},
								{4, 1,
								{{1, 0, 0, 0},
								 {1, 0, 0, 0},
								 {1, 0, 0, 0},
								 {1, 0, 0, 0}},
								{0, 0, 0, 0},
								{0, 0, 0, 0},
								{3, 0, 0, 0},
} };

static STFigurePos FIG_POS_Z[] = { {3, 2,
								{{1, 0, 0, 0},
								 {1, 1, 0, 0},
								 {0, 1, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 1, 0},
								{0, 1, 1, 0},
								{1, 2, 0, 0},
								},
								{2, 3,
								{{0, 1, 1, 0},
								 {1, 1, 0, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{1, 0, 0, 0},
								{2, 1, 0, 0},
								{1, 1, 0, 0},
								} 
};

static STFigurePos FIG_POS_REV_Z[] = { {3, 2,
								{{0, 1, 0, 0},
								 {1, 1, 0, 0},
								 {1, 0, 0, 0},
								 {0, 0, 0, 0}},
								{1, 0, 0, 0},
								{1, 1, 0, 0},
								{2, 1, 0, 0},
								},
								{2, 3,
								{{1, 1, 0, 0},
								 {0, 1, 1, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 1, 0, 0},
								{1, 2, 0, 0},
								{0, 1, 1, 0}
} };

static STFigurePos FIG_POS_R[] = { {3, 2,
								{{1, 1, 0, 0},
								 {1, 0, 0, 0},
								 {1, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{1, 0, 0, 0},
								{2, 0, 0, 0}
								},
								{2, 3,
								{{1, 1, 1, 0},
								 {0, 0, 1, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 2, 0, 0},
								{2, 2, 0, 0},
								{0, 0, 1, 0}
								},
								{3, 2,
								{{0, 1, 0, 0},
								 {0, 1, 0, 0},
								 {1, 1, 0, 0},
								 {0, 0, 0, 0}},
								{1, 1, 0, 0},
								{1, 1, 1, 0},
								{2, 2, 0, 0}
								},
								{2, 3,
								{{1, 0, 0, 0},
								 {1, 1, 1, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{0, 2, 0, 0},
								{1, 1, 1, 0}
								}
};

static STFigurePos FIG_POS_REV_R[] = {
								{3, 2,
								{{1, 1, 0, 0},
								 {0, 1, 0, 0},
								 {0, 1, 0, 0},
								 {0, 0, 0, 0}},
								{0, 1, 1, 0},
								{1, 1, 1, 0},
								{0, 2, 0, 0}
								},
								{2, 3,
								{{0, 0, 1, 0},
								 {1, 1, 1, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{2, 0, 0, 0},
								{2, 2, 0, 0},
								{1, 1, 1, 0}
								},
								{3, 2,
								{{1, 0, 0, 0},
								 {1, 0, 0, 0},
								 {1, 1, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{0, 0, 1, 0},
								{2, 2, 0, 0}
								},
								{2, 3,
								{{1, 1, 1, 0},
								 {1, 0, 0, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{2, 0, 0, 0},
								{1, 0, 0, 0}
								}
};

static STFigurePos FIG_POS_T[] = {
								{2, 3,
								{{1, 1, 1, 0},
								 {0, 1, 0, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 1, 0, 0},
								{2, 1, 0, 0},
								{0, 1, 0, 0}
								},
								{3, 2,
								{{0, 1, 0, 0},
								 {1, 1, 0, 0},
								 {0, 1, 0, 0},
								 {0, 0, 0, 0}},
								{1, 0, 1, 0},
								{1, 1, 1, 0},
								{1, 2, 0, 0}
								},
								{2, 3,
								{{0, 1, 0, 0},
								 {1, 1, 1, 0},
								 {0, 0, 0, 0},
								 {0, 0, 0, 0}},
								{1, 0, 0, 0},
								{1, 2, 0, 0},
								{1, 1, 1, 0}
								},
								{3, 2,
								{{1, 0, 0, 0},
								 {1, 1, 0, 0},
								 {1, 0, 0, 0},
								 {0, 0, 0, 0}},
								{0, 0, 0, 0},
								{0, 1, 0, 0},
								{2, 1, 0, 0}
								}
};

static size_t FIG_POS_COUNTS[] = {
	sizeof(FIG_POS_SQUARE) / sizeof(STFigurePos),
	sizeof(FIG_POS_LINE) / sizeof(STFigurePos),
	sizeof(FIG_POS_Z) / sizeof(STFigurePos),
	sizeof(FIG_POS_REV_Z) / sizeof(STFigurePos),
	sizeof(FIG_POS_R) / sizeof(STFigurePos),
	sizeof(FIG_POS_REV_R) / sizeof(STFigurePos),
	sizeof(FIG_POS_T) / sizeof(STFigurePos)
};

const std::string& fig_type_to_str(ENTFigureType tp) {
	return FIG_TYPE_STR[tp];
}

int load_positions() {
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_SQUARE]; ++i)
		FIG_POSITIONS[FIG_SQUARE].push_back(&FIG_POS_SQUARE[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_LINE]; ++i)
		FIG_POSITIONS[FIG_LINE].push_back(&FIG_POS_LINE[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_Z]; ++i)
		FIG_POSITIONS[FIG_Z].push_back(&FIG_POS_Z[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_REV_Z]; ++i)
		FIG_POSITIONS[FIG_REV_Z].push_back(&FIG_POS_REV_Z[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_R]; ++i)
		FIG_POSITIONS[FIG_R].push_back(&FIG_POS_R[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_REV_R]; ++i)
		FIG_POSITIONS[FIG_REV_R].push_back(&FIG_POS_REV_R[i]);
	for (unsigned i = 0; i < FIG_POS_COUNTS[FIG_T]; ++i)
		FIG_POSITIONS[FIG_T].push_back(&FIG_POS_T[i]);
	return 0;
};

void print_positions() {
	printf("LOADED POSITIONS:\n");
	for (unsigned i = 0; i < FIG_COUNT; ++i) {
		printf("Type: %s\n", fig_type_to_str((ENTFigureType)i).c_str());
		CFigure f((ENTFigureType)i, 0);
		for (int k = 0; k < FIG_POSITIONS[i].size(); ++k) {
			f.print_pos();
			printf("\n");
			f.next_pos();
		}
	}
}

int get_figure_count()
{
	return FIG_COUNT;
}

int get_figure_pos_count(ENTFigureType tp)
{
	return FIG_POSITIONS[tp].size();
}

