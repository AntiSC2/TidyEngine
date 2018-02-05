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
#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include "resource.hpp"

typedef unsigned int GLuint;

class Shader: public Resource {
public:
	Shader() = default;
	Shader(const std::string &vertex, const std::string &fragment);
	virtual ~Shader();

	virtual std::string Type();

	void SetSources(const std::string &vertex, const std::string &fragment);
	void AddAttribute(const std::string &attribute);
	bool InitProgram();
	bool LinkProgram();
	GLuint GetUniformLoc(const std::string &name);

	void SetUniform1f(const std::string &name, float value);
	void SetUniform1fv(const std::string &name, float *value, int count);
	void SetUniform1i(const std::string &name, int value);
	void SetUniform1iv(const std::string &name, int *value, int count);
	void SetUniform2f(const std::string &name, glm::vec2 vec);
	void SetUniform3f(const std::string &name, glm::vec3 vec);
	void SetUniform4f(const std::string &name, glm::vec4 vec);
	void SetUniformMat3(const std::string &name, glm::mat3 matrix);
	void SetUniformMat4(const std::string &name, glm::mat4 matrix);

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
