#version 330 core
in vec4 Color;
in vec2 UV;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main() {
	color = texture2D(texture_diffuse1, UV) * Color;
}