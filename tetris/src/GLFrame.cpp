#include <GLFrame.h>

GLFrame::GLFrame()
{
	m_coords = { -0.99f, 1.0f, 1.0f, 1.0f, 1.0f, -0.99f, -0.99f, -0.99f };
}

int GLFrame::LoadToGL()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_coords.size() * sizeof(float), m_coords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_count = (int) m_coords.size() / 2;
	return 0;
}

void GLFrame::Render()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINE_LOOP, 0, m_count);
	glBindVertexArray(0);
}

static GLFrame frame_object;

GLFrame& GetFrameObject()
{
	return frame_object;
}