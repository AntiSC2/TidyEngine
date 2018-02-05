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

#include "material.hpp"
#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include "texture.hpp"
#include "shader.hpp"

Material::Material(glm::vec4 ambient, glm::vec4 diff, glm::vec4 spec, std::vector<Texture*> diffuse, std::vector<Texture*> specular, float shine)
{
	m_AmbientC = ambient;
	m_DiffuseC = diff;
	m_SpecC = spec;
	m_Diffuse = diffuse;
	m_Specular = specular;
	m_Shine = shine;
}

bool Material::Textured() const
{
	if (m_Diffuse.size() != 0 || m_Specular.size() != 0)
    	return true;
	else
		return false;
}

std::string Material::Type()
{
	return "Material";
}

void Material::Bind(Shader *shader) const
{
	if (shader == nullptr)
		return;
	uint8_t count = 1;

	if (Textured()) {
		for (size_t i = 0; i < m_Diffuse.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			shader->SetUniform1i("material.diffuse" + (char)(count + 48), i);
			count++;
			glBindTexture(GL_TEXTURE_2D, m_Diffuse[i]->GetTex());
		}

		uint8_t old_i = count;
		count = 1;

		if (m_Specular.size() == 0)
			shader->SetUniform1i("texture_spec", 0);
		else
			shader->SetUniform1i("texture_spec", 1);

		for (size_t i = 0; i < m_Specular.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i + old_i);
			shader->SetUniform1i("material.specular" + (char)(count + 48), i);
			count++;
			glBindTexture(GL_TEXTURE_2D, m_Specular[i]->GetTex());
		}

		glActiveTexture(GL_TEXTURE0);
	} else {
		shader->SetUniform4f("material.ambient", m_AmbientC);
		shader->SetUniform4f("material.diffuse", m_DiffuseC);
		shader->SetUniform4f("material.specular", m_SpecC);
	}

	shader->SetUniform1f("material.shine", m_Shine);
}