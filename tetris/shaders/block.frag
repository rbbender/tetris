#version 330 core

in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
	//gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
	gl_FragColor = texture(tex, TexCoord);
}