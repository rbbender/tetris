#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLDefs.h"

typedef std::vector<float> TFrameCoords;

class GLFrame :
	public IGLObject
{
protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLsizei m_count;

	TFrameCoords m_coords;

public:
	GLFrame();
	int LoadToGL();
	void Render();
};

GLFrame& GetFrameObject();
