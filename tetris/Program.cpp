#include "Program.h"
#include <iostream>

int Program::program_cnt = 0;

int Program::GetUniformLocations()
{
	if (!pVertexShader || !pFragmentShader) {
		std::cout << GetRepr() << "Some shaders are not set, won't be able to get uniforms"
			<< std::endl;
		return -1;
	}
	std::vector<std::string> uniforms = pVertexShader->GetUniforms();
	for (auto i = uniforms.cbegin(), e = uniforms.cend();
		i != e; ++i) {
		GLint l = glGetUniformLocation(hndlGLObj, i->c_str());
		m_uniforms[*i] = l;
		std::cout << GetRepr() << pVertexShader->GetRepr() << *i << "=" << l << std::endl;
	}
	uniforms = pFragmentShader->GetUniforms();
	for (auto i = uniforms.cbegin(), e = uniforms.cend();
		i != e; ++i) {
		GLint l = glGetUniformLocation(hndlGLObj, i->c_str());
		m_uniforms[*i] = l;
		std::cout << GetRepr() << pFragmentShader->GetRepr() << *i << "=" << l << std::endl;
	}
	std::cout << GetRepr() << "Uniform locations defined" << std::endl;
	return 0;
}

Program::Program():
	hndlGLObj(0),
	idx(++program_cnt),
	pVertexShader(nullptr),
	pFragmentShader(nullptr)
{
	std::cout << GetRepr() << "CREATED" << std::endl;
}

Program::Program(Shader& vertexShader, Shader& fragmentShader):
	Program()
{
	pVertexShader = &vertexShader;
	pFragmentShader = &fragmentShader;
}

const std::string Program::GetRepr() const
{
	char msg[1024];
	sprintf_s(msg, "PR[%u]:", idx);
	return std::string(msg);
}

int Program::AddShader(Shader& shader)
{
	switch (shader.GetType()) {
	case SH_T_VERTEX:
		pVertexShader = &shader;
		break;
	case SH_T_FRAGMENT:
		pFragmentShader = &shader;
		break;
	default:
		return -1;
	}
	return 0;
}

int Program::Link()
{
	if (!pVertexShader || !pFragmentShader) {
		std::cout << GetRepr() << "Not all shaders set" << std::endl;
		return 1;
	}
	if (!pVertexShader->GetGLId()) {
		if (pVertexShader->Compile()) {
			std::cout << GetRepr() << "Unable to compile vertex shader" << std::endl;
			return 2;
		}
	}
	if (!pFragmentShader->GetGLId()) {
		if (pFragmentShader->Compile()) {
			std::cout << GetRepr() << "Unable to compile fragment shader" << std::endl;
			return 3;
		}
	}

	hndlGLObj = glCreateProgram();

	std::cout << GetRepr() << "GL OBJ CREATED: " << hndlGLObj << std::endl;

	glAttachShader(hndlGLObj, pVertexShader->GetGLId());
	glAttachShader(hndlGLObj, pFragmentShader->GetGLId());

	glLinkProgram(hndlGLObj);
	GLint res;
	glGetProgramiv(hndlGLObj, GL_LINK_STATUS, &res);
	if (!res) {
		char msg[1024];
		glGetProgramInfoLog(hndlGLObj, sizeof(msg), nullptr, msg);
		std::cout << GetRepr() << "Unable to link: '" << msg << "'" << std::endl;
		return 5;
	}

	GetUniformLocations();

	return 0;
}

void Program::Use()
{
	if (hndlGLObj)
		glUseProgram(hndlGLObj);
}

GLint Program::GetUniformLocation(std::string s_uniform_name)
{
	HUniformsIt res = m_uniforms.find(s_uniform_name);
	if (res == m_uniforms.cend())
		return -1;
	return res->second;
}

void Program::CleanupShaders()
{
	if (pVertexShader)
		delete pVertexShader;
	if (pFragmentShader)
		delete pFragmentShader;
	pVertexShader = nullptr;
	pFragmentShader = nullptr;
}

Program::~Program()
{
	if (hndlGLObj)
		glDeleteProgram(hndlGLObj);
	std::cout << "PR[" << idx << "]:DELETED" << std::endl;
}
