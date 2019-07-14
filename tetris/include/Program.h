#pragma once
#include <glad/glad.h>
#include <map>
#include <string>
#include "Shader.h"

class Program
{
	typedef std::map<std::string, GLint> HUniforms;
	typedef HUniforms::const_iterator HUniformsIt;
	static int program_cnt;
	GLuint hndlGLObj;
	const int idx;
	Shader* pVertexShader;
	Shader* pFragmentShader;
	std::map<std::string, GLint> m_uniforms;
private:
	int GetUniformLocations();
public:
	Program();
	Program(Shader& vertexShader, Shader& fragmentShader);
	GLuint GetGLId() { return hndlGLObj; };
	const std::string GetRepr() const;
	int GetId() { return idx; };
	int AddShader(Shader& shader);
	int Link();
	void Use();
	GLint GetUniformLocation(std::string s_uniform_name);
	void CleanupShaders();
	~Program();
};
