#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform ivec2 simple_c;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4((simple_c.x + aPos.x) / 16.0 - 1.0, (simple_c.y + aPos.y)/-12.0 + 1.0, 0, 1);
	TexCoord = aTexCoord;
}