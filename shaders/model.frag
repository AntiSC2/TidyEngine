#version 330 core
in vec4 Color;
in vec2 UV;
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
	sampler2D diffuse1;
	sampler2D specular1;
	vec3 ambient;
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

	vec3 ambient = light1.ambient * vec3(texture2D(material.diffuse1, UV));
	vec3 specular = light1.specular * (vec3(texture2D(material.specular1, UV)) * spec);
	vec3 diffuse = light1.diffuse * vec3(diff * texture2D(material.diffuse1, UV) * Color);

	vec3 result = ambient + specular + diffuse;
	color = vec4(result, 1.0f);
}