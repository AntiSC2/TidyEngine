#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 3) in vec3 normal;

out vec4 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 model;
uniform mat3 inverseModel;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	Color = color;
	Normal = inverseModel * normal;  
	FragPos = vec3(model * vec4(position, 1.0));
}
