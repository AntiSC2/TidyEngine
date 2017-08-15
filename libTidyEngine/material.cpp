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
#include "texture.hpp"
#include "shader.hpp"

Material::Material()
{
	;
}

Material::Material(glm::vec4 color)
{
	m_DiffuseC = c;
}

Material::Material(std::vector<Texture*> diffuse, std::vector<Texture*> specular)
{
	m_Diffuse = diffuse;
	m_Specular = specular;
}

Material::~Material()
{
	;
}

void Material::Bind(Shader *shader) const
{
	if (shader == nullptr)
		return;
	uint8_t count = 1;

	for (size_t i = 0; i < m_Diffuse.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		shader->SetUniform1i("material.diffuse" + (char)(count + 48), i);
		count++;
		glBindTexture(GL_TEXTURE_2D, m_Diffuse[i]->GetTex());
	}

	uint8_t old_i = count;
	count = 1;
	for (size_t i = 0; i < m_Specular.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i + old_i);
		shader->SetUniform1i("material.specular" + (char)(count + 48), i);
		count++;
		glBindTexture(GL_TEXTURE_2D, m_Specular[i]->GetTex());
	}
	glActiveTexture(GL_TEXTURE0);
}