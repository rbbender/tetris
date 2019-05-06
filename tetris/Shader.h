#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

enum SHADER_TYPE {
	SH_T_UNKNOWN,
	SH_T_VERTEX,
	SH_T_FRAGMENT
};


class Shader
{
	static int shader_cnt;
	const SHADER_TYPE sh_type;
	const std::string src;
	const int idx;
	GLuint		hndlGLObj;
	const std::vector<std::string> v_uniforms;
public:
	Shader(SHADER_TYPE type, const std::string& shader_src,
		const std::vector<std::string> uniforms);
	int Compile();
	GLuint GetGLId() const { return hndlGLObj; };
	int GetId() const { return idx; };
	const std::string GetRepr();
	SHADER_TYPE GetType() const { return sh_type; };
	std::vector<std::string> GetUniforms();
	~Shader();
};

const std::string& GetShaderTypeStr(SHADER_TYPE type);

GLenum GetGLShaderType(SHADER_TYPE type);

Shader* LoadShaderFromFile(SHADER_TYPE type, const char file_name[], const std::vector<std::string>& uniforms);
