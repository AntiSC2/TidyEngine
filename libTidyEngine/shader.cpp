/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
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
