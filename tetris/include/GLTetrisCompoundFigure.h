#pragma once
#include "GLFigure.h"
class CFigure;

class GLTetrisCompoundFigure :
	public GLFigure
{
public:
	void AddFigure(int x, int y, const GLFigure& figure);
	static GLTetrisCompoundFigure* FromFigure(CFigure&);
};

