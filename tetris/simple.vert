#version 330 core
layout (location=0) in vec2 aPos;

void main() {
	gl_Position = vec4(aPos.x / 320 - 1.0, aPos.y / 240 + 0.5, 0.0, 1.0);
}