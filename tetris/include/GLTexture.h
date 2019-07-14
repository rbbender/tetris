#pragma once
#include "GLDefs.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef std::vector<float> TTexCoords;
typedef TTexCoords::const_iterator TTexCoordsCIt;
typedef TTexCoords::iterator TTexCoordsIt;

class GLTexture :
	public IGLObject
{
	static GLuint texCount;
	GLuint m_texObject;
	GLenum m_textureNumber;
	int m_x;
	int m_y;
	int m_channels;
	unsigned char* m_img;
	TTexCoords m_texCoords;
public:
	GLTexture();
	bool LoadTexture(const char* fileName);
	int LoadToGL();
	void Use();
	GLuint GetGLObject() { return m_texObject; };
	void SetCoords(const TTexCoords& coords);
	const TTexCoords& GetCoords() const { return m_texCoords; };
};

