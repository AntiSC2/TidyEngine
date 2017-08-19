#version 330 core
in vec4 Color;
in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Material {
	sampler2D diffuse1;
	sampler2D specular1;
	float shine;
};

uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec3 lightColor;
uniform Material material;

void main() {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 ambient = ambientStrength * lightColor;
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f) + texture2D(material.diffuse1, UV) * Color * vec4(ambient + diff, 0.0f);
}