#version 330 core
in vec4 Color;
in vec2 UV;

out vec4 color;

uniform sampler2D tex;

void main() {
	color = texture2D(tex, UV) * Color;
}