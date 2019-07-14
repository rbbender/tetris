#include "GLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint GLTexture::texCount = 0;

GLTexture::GLTexture():
	IGLObject(),
	m_texObject(0),
	m_textureNumber(GL_TEXTURE0 + texCount++),
	m_x(0),
	m_y(0),
	m_channels(0),
	m_img(nullptr)
{
	std::cout << "GL_TEXTURE" << m_textureNumber - GL_TEXTURE0 << std::endl;
}

bool GLTexture::LoadTexture(const char* fileName)
{
	m_img = stbi_load(fileName, &m_x, &m_y, &m_channels, 0);
	if (!m_img) {
		std::cout << "ERROR: unable to load image from file " << fileName << std::endl;
		return false;
	}
	std::cout << "Loaded image from file " << fileName << std::endl;
	std::cout << "X: " << m_x << "\tY: " << m_y << "\tchannels: " << m_channels << std::endl;
	return true;
}

int GLTexture::LoadToGL()
{
	if (!m_img) {
		std::cout << "ERROR:: no image loaded, won't load to GL\n";
		return 1;
	}
	glGenTextures(1, &m_texObject);
	glBindTexture(GL_TEXTURE_2D, m_texObject);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_x, m_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(m_img);
	m_img = nullptr;
	return 0;
}

void GLTexture::Use()
{
	if (!m_texObject) {
		std::cout << "ERROR:: no texture loaded, won't use it\n";
		return;
	}
	//std::cout << "Using texture: " << m_textureNumber << std::endl;
	glBindTexture(GL_TEXTURE_2D, m_texObject);
	//glActiveTexture(m_textureNumber);
}

void GLTexture::SetCoords(const TTexCoords& coords)
{
	m_texCoords = coords;
}

