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

#include <vector>
#include <glm/vec4.hpp>
#include "resource.hpp"

class Texture;
class Shader;

class Material: public Resource {
public:
	Material() = default;
	Material(glm::vec4 ambient, glm::vec4 diff, glm::vec4 spec, std::vector<Texture*> diffuse, std::vector<Texture*> specular, float shine);
	virtual ~Material() = default;

	virtual bool Textured() const;
	virtual std::string Type();
	virtual void Bind(Shader *shader) const;
protected:
	std::vector<Texture*> m_Diffuse;
	std::vector<Texture*> m_Specular;
	glm::vec4 m_AmbientC;
	glm::vec4 m_DiffuseC;
	glm::vec4 m_SpecC;
	float m_Shine = 32.0f;
};