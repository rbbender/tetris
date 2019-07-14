#include "GLTetrisCompoundFigure.h"
#include <Figure.h>

void GLTetrisCompoundFigure::AddFigure(int x, int y, const GLFigure& figure)
{
	if (m_vao) {
		std::cout << "ERROR:: " << GetGLObjID() << ":: Object already loaded into GL\n";
		return;
	}
	TCoordsCIt beg = figure.GetCoords().cbegin(), end = figure.GetCoords().cend();
	if (figure.GetCoords().size() % 2) {
		std::cout << "ERROR:: " << figure.GetGLObjID() <<":: Coords count is not even\n";
		return;
	}
	for (TCoordsCIt i = beg; i < end; i += 2) {
		m_coords.push_back(*i + x);
		m_coords.push_back(*(i + 1) + y);
	}

	m_texcoords.insert(m_texcoords.cend(), figure.GetTextureCoords().cbegin(),
		figure.GetTextureCoords().cend());

	return;
}

GLTetrisCompoundFigure* GLTetrisCompoundFigure::FromFigure(CFigure& figure)
{
	auto result = new GLTetrisCompoundFigure;
	for (int y = 0; y < (*(figure.get_pos()))->size_y; ++y)
		for (int x = 0; x < (*(figure.get_pos()))->size_x; ++x)
			;

	return nullptr;
}
