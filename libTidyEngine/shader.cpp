/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
*/

#include "shader.hpp"
#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>
#include "iomanager.hpp"

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
	SetSources(vertex, fragment);
}

Shader::~Shader()
{
	if (m_ProgramID != 0)
		glDeleteProgram(m_ProgramID);
}

std::string Shader::Type() {
	return "Shader";
}

void Shader::SetSources(const std::string &vertex, const std::string &fragment)
{
	m_VertexSource = vertex;
	m_FragmentSource = fragment;
}

void Shader::AddAttribute(const std::string &attribute)
{
	glBindAttribLocation(m_ProgramID, m_Attributes, attribute.c_str());
	m_Attributes++;
}	

bool Shader::InitProgram()
{
	m_ProgramID = glCreateProgram();
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_ProgramID == 0 || m_VertexID == 0 || m_FragmentID == 0) {
		printf("Warning: failed to create shader program!\n");
		
		m_ProgramID = 0;
		m_VertexID = 0;
		m_FragmentID = 0;
		
		return false;
	}

	bool compile_finish = false;
	compile_finish = CompileShader(m_VertexSource, m_VertexID);
	if (compile_finish)
		compile_finish = CompileShader(m_FragmentSource, m_FragmentID);
	
	return compile_finish;
}

bool Shader::LinkProgram()
{
	glAttachShader(m_ProgramID, m_VertexID);
	glAttachShader(m_ProgramID, m_FragmentID);
	glLinkProgram(m_ProgramID);

	GLint is_linked = 0;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int* )&is_linked);

	if (is_linked == GL_FALSE) {
		GLint max_length = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &max_length);

		char *log = new char[max_length];
		glGetProgramInfoLog(m_ProgramID, max_length, &max_length, log);

		glDeleteProgram(m_ProgramID);
		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);

		printf("%s", log);
		delete log;
		log = nullptr;
		printf("Warning: shaders failed to link!\n");

		m_ProgramID = 0;
		m_VertexID = 0;
		m_FragmentID = 0;

		return false;
	}
	
	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	return true;
}

bool Shader::CompileShader(const std::string &filepath, GLuint shader_id)
{
	std::string source = "";
	source = IO.ReadFile(filepath);

	const char* pointer_source = source.c_str();

	glShaderSource(shader_id, 1, &pointer_source, nullptr);
	glCompileShader(shader_id);
	
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	
	if (success == GL_FALSE) {
		GLint max_length = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

		char *log = new char[max_length];
		glGetShaderInfoLog(shader_id, max_length, &max_length, log);

		glDeleteShader(shader_id);

		printf("%s", log);
		delete log;
		log = nullptr;
		printf("Warning: shader failed to compile!\n");

		m_ProgramID = 0;
		m_VertexID = 0;
		m_FragmentID = 0;

		return false;
	}
	return true;
}

GLuint Shader::GetUniformLoc(const std::string &name)
{
	return glGetUniformLocation(m_ProgramID, name.c_str());
}

void Shader::SetUniform1f(const std::string &name, float value)
{
	glUniform1f(GetUniformLoc(name), value);
}

void Shader::SetUniform1fv(const std::string &name, float *value, int count)
{
	glUniform1fv(GetUniformLoc(name), count, value);
}

void Shader::SetUniform1i(const std::string &name, int value)
{
	glUniform1i(GetUniformLoc(name), value);
}

void Shader::SetUniform1iv(const std::string &name, int *value, int count)
{
	glUniform1iv(GetUniformLoc(name), count, value);
}

void Shader::SetUniform2f(const std::string &name, glm::vec2 vec)
{
	glUniform2f(GetUniformLoc(name), vec.x, vec.y);
}

void Shader::SetUniform3f(const std::string &name, glm::vec3 vec)
{
	glUniform3f(GetUniformLoc(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniform4f(const std::string &name, glm::vec4 vec)
{
	glUniform4f(GetUniformLoc(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat3(const std::string &name, glm::mat3 matrix)
{
	glUniformMatrix3fv(GetUniformLoc(name), 1, GL_FALSE,
			glm::value_ptr(matrix));
}

void Shader::SetUniformMat4(const std::string &name, glm::mat4 matrix)
{
	glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE,
			glm::value_ptr(matrix));
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
	for (GLuint i = 0; i < m_Attributes; i++)
		glEnableVertexAttribArray(i);
}

void Shader::UnBind() const
{
	glUseProgram(0);
	for (GLuint i = 0; i < m_Attributes; i++)
		glDisableVertexAttribArray(i);
}
