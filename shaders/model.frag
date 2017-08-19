#version 330 core
in vec4 Color;
in vec2 UV;

out vec4 color;

struct Material {
	sampler2D diffuse1;
	sampler2D specular1;
	float shine;
}

uniform Material material;

void main() {
	color = Vec4(0.0f, 0.0f, 0.0f, 1.0f) + texture2D(material.diffuse1, UV) * Color;
}