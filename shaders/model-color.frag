#version 330 core
in vec4 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Light {
	vec3 ambient;
	vec3 pos;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shine;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light1;

/* Phong Lightning Shader
 */

void main() {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light1.pos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(Normal, halfwayDir), 0.0f), material.shine);

	vec4 ambient = vec4(light1.ambient, 1.0f) * material.ambient;
	vec4 specular = vec4(light1.specular, 1.0f) * material.specular * spec;
	vec4 diffuse = vec4(light1.diffuse, 1.0f) * diff * material.diffuse * Color;

	vec4 result = ambient + specular + diffuse;
	result.a = material.diffuse.a;
	color = result;
}