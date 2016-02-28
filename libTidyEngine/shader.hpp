/*
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
*/

#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader {
public:
	Shader();
	Shader(std::string vertex, std::string fragment);
	~Shader();

	void SetSources(std::string vertex, std::string fragment);
	void AddAttribute(std::string attribute);
	bool InitProgram();
	bool LinkProgram();
	void Bind();
	void UnBind();
private:
	bool CompileShader(std::string file_path, GLuint shader_id);
	GLuint m_Attributes = 0;
	GLuint m_ProgramID = 0;
	GLuint m_VertexID = 0;
	GLuint m_FragmentID = 0;
	std::string m_VertexSource = "";
	std::string m_FragmentSource = "";
};
