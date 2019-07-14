#pragma once
#include <vector>
#include "GLFigure.h"

class GLBlock: public GLFigure {
public:
	GLBlock();
};

GLBlock& GetBlockInstance();
