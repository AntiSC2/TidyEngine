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
#include "iomanager.hpp"

Shader::Shader()
{
	;
}

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
	SetSources(vertex, fragment);
}

Shader::~Shader()
{
	if (m_ProgramID != 0)
		glDeleteProgram(m_ProgramID);
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
		printf("Error: failed to create shader program!\n");
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

		printf("%s\n", log);
                delete log;
                log = nullptr;
		printf("Error: shaders failed to link!\n");
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

		printf("%s\n", log);
                delete log;
                log = nullptr;
		printf("Error: shader failed to compile!\n");
		return false;
	}
	return true;
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
