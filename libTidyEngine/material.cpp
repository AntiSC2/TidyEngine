/*
TidyEngine
Copyright (C) 2017 Jakob Sinclair

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
	printf("R: %f G: %f B: %f A: %f\n", m_AmbientC.x, m_AmbientC.y, m_AmbientC.z, m_DiffuseC.w);
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