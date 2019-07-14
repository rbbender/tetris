#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLDefs.h"
#include "GLTexture.h"

class GLFigure :
	public IGLObject
{
protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_vbo_tex;
	GLsizei m_count;
	TCoords m_coords;
	TTexCoords m_texcoords;
public:
	GLFigure();
	const TCoords& GetCoords() const;
	int LoadToGL();
	void Render();
	void SetTextureCoords(const GLTexture& texture);
	const TTexCoords& GetTextureCoords() const { return m_texcoords; };
};

