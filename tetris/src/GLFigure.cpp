#include "GLFigure.h"

GLFigure::GLFigure():
	IGLObject(),
	m_vao(0),
	m_vbo(0),
	m_vbo_tex(0),
	m_count(0),
	m_coords(),
	m_texcoords()
{
}

const TCoords& GLFigure::GetCoords() const
{
	return m_coords;
}

int GLFigure::LoadToGL()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_coords.size()*sizeof(unsigned), m_coords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, (void*)0);
	glGenBuffers(1, &m_vbo_tex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_tex);
	glBufferData(GL_ARRAY_BUFFER, m_texcoords.size() * sizeof(float),
		m_texcoords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_count = (int) m_coords.size() / 2;
	return 0;
}

void GLFigure::Render()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_count);
	glBindVertexArray(0);
}

void GLFigure::SetTextureCoords(const GLTexture& texture)
{
	m_texcoords = texture.GetCoords();
}
