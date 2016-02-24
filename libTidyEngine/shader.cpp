/*
Copyright (C) 2015 Jakob Sinclair

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
*/

#include "shader.hpp"

Shader::Shader()
{
	;
}

Shader::Shader(std::string vertex, std::string fragment)
{
	SetSources(vertex, fragment);
}

Shader::~Shader()
{
	if (m_ProgramID != 0)
		glDeleteProgram(m_ProgramID);
}

void Shader::SetSources(std::string vertex, std::string fragment)
{
	m_VertexSource = vertex;
	m_FragmentSource = fragment;
}

void Shader::AddAttribute(std::string attribute)
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

		char log[max_length];
		glGetProgramInfoLog(m_ProgramID, max_length, &max_length, log);

		glDeleteProgram(m_ProgramID);
		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);

		printf("%s\n", log);
		printf("Error: shaders failed to link!\n");
		return false;
	}
	
	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	return true;
}

bool Shader::CompileShader(std::string file_path, GLuint shader_id)
{
	std::ifstream source(file_path);
	if (source.fail()) {
		printf("Error: failed to open %s!\n", file_path.c_str());
		return false;
	}

	std::string source_contents = "";
	std::string line = "";

	while (std::getline(source, line))
		source_contents += line + '\n';

	source.close();
	const char* pointer_source = source_contents.c_str();

	glShaderSource(shader_id, 1, &pointer_source, nullptr);
	glCompileShader(shader_id);
	
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	
	if (success == GL_FALSE) {
		GLint max_length = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

		char log[max_length];
		glGetShaderInfoLog(shader_id, max_length, &max_length, log);

		glDeleteShader(shader_id);

		printf("%s\n", log);
		printf("Error: shader failed to compile!\n");
		return false;
	}
	return true;
}

void Shader::Bind()
{
	glUseProgram(m_ProgramID);
	for (GLuint i = 0; i < m_Attributes; i++)
		glEnableVertexAttribArray(i);
}

void Shader::UnBind()
{
	glUseProgram(0);
	for (GLuint i = 0; i < m_Attributes; i++)
		glDisableVertexAttribArray(i);
}
