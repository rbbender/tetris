#include "GLBlock.h"

GLBlock::GLBlock():
	GLFigure()
{
	m_coords = { 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1};
}

static GLBlock block_instance;

GLBlock& GetBlockInstance()
{
	return block_instance;
}
