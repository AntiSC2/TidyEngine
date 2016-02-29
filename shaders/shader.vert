#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

out vec4 Color;
out vec2 UV;

void main() {
	gl_Position = vec4(position, 1.0);
	Color = color;
	UV = uv;
}
