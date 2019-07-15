#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
	gl_Position = view * model * vec4(aPos, 0.0f, 1.0f);
	TexCoord = aTexCoord;
}