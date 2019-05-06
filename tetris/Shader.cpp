#include "Shader.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

const std::string SH_T_STR_UNKNOWN("SH_T_UNKNOWN");
const std::string SH_T_STR_VERTEX("SH_T_VERTEX");
const std::string SH_T_STR_FRAGMENT("SH_T_FRAGMENT");

const std::vector<std::string> SH_T_STR = { SH_T_STR_UNKNOWN, SH_T_STR_VERTEX, SH_T_STR_FRAGMENT };

int Shader::shader_cnt = 0;

Shader::Shader(SHADER_TYPE type, const std::string& shader_src,
	std::vector<std::string> uniforms):
	sh_type(type),
	src(shader_src),
	idx(++shader_cnt),
	hndlGLObj(0),
	v_uniforms(uniforms)
{
	std::cout << GetRepr() << ":CREATED" << std::endl;
	std::cout << "Source:\n" << src << std::endl;
}

int Shader::Compile()
{
	if (!(hndlGLObj = glCreateShader(GetGLShaderType(sh_type)))) {
		std::cout << GetRepr() << ":FAILED TO CREATE GL OBJ" << std::endl;
		return -1;
	}
	std::cout << GetRepr() << "GL OBJ CREATED: " << hndlGLObj << std::endl;
	const char* sh_src = src.c_str();
	glShaderSource(hndlGLObj, 1, &sh_src, nullptr);
	glCompileShader(hndlGLObj);
	GLint res;
	glGetShaderiv(hndlGLObj, GL_COMPILE_STATUS, &res);
	if (!res) {
		char msg[1024];
		glGetShaderInfoLog(hndlGLObj, sizeof(msg), nullptr, msg);
		std::cout << GetRepr() << ":Failed to compile: " << msg;
		return -4;
	}
	std::cout << GetRepr() << ":Compiled"
		<< std::endl;
	return 0;
}

const std::string Shader::GetRepr()
{
	char repr[256];
	sprintf_s(repr, "SH[%u]:%s:", GetId(), GetShaderTypeStr(sh_type).c_str());
	return std::string(repr);
}

std::vector<std::string> Shader::GetUniforms()
{
	return v_uniforms;
}

Shader::~Shader()
{
	if (hndlGLObj)
		glDeleteShader(hndlGLObj);
	hndlGLObj = 0;
	std::cout << GetRepr() << ":DELETED" << std::endl;
}

const std::string& GetShaderTypeStr(SHADER_TYPE type)
{
	return SH_T_STR[type];
}

GLenum GetGLShaderType(SHADER_TYPE type)
{
	switch (type) {
	case SH_T_VERTEX:
		return GL_VERTEX_SHADER;
	case SH_T_FRAGMENT:
		return GL_FRAGMENT_SHADER;
	default:
		return 0;
	}
}

Shader* LoadShaderFromFile(SHADER_TYPE type, const char file_name[],
	const std::vector<std::string>& uniforms) {
	char shader_src_buf[1024];
	FILE* inp;
	errno_t r;
	char error_msg[1024];
	r = fopen_s(&inp, file_name, "r");
	if (!inp) {
		strerror_s(error_msg, 1024, r);
		std::cout << "Unable to open file '" << file_name << "', error:";
		std::cout << error_msg << std::endl;
		return nullptr;
	}
	unsigned len = 0;
	int c;
	while ((c = std::fgetc(inp)) != EOF && len < 1024)
		shader_src_buf[len++] = c;
	shader_src_buf[len] = 0;
	fclose(inp);
	std::string src(shader_src_buf);
	Shader* res = new Shader(type, src, uniforms);
	return res;
}