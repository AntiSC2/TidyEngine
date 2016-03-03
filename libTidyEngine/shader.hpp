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

#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
public:
	Shader();
	Shader(const std::string &vertex, const std::string &fragment);
	~Shader();

	void SetSources(const std::string &vertex, const std::string &fragment);
	void AddAttribute(const std::string &attribute);
	bool InitProgram();
	bool LinkProgram();
	void Bind() const;
	void UnBind() const;
private:
	bool CompileShader(const std::string &filepath, GLuint shader_id);

	GLuint m_Attributes = 0;
	GLuint m_ProgramID = 0;
	GLuint m_VertexID = 0;
	GLuint m_FragmentID = 0;
	std::string m_VertexSource = "";
	std::string m_FragmentSource = "";
};
