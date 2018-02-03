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

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include <glad/glad.h>
#include "modelrenderer.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"

ModelRenderer::ModelRenderer()
{
	m_Light.SetPos(glm::vec3(10.0f, 10.0f, 2.0f));	
}

void ModelRenderer::Initialise(Shader *shader)
{
	m_Shader = shader;
}

void ModelRenderer::Initialise(Shader *shader, Shader *color)
{
	m_Shader = shader;
	m_ColorShader = color;
}

void ModelRenderer::Begin()
{
	m_Models.clear();
}

void ModelRenderer::Draw(Model *m)
{
	m_Models.push_back(m);
}

void ModelRenderer::End()
{
	;
}

void ModelRenderer::Present()
{
	if (m_Camera == nullptr)
		return;

	if (m_Shader == nullptr)
		return;
	m_Shader->Bind();
	m_Shader->SetUniform3f("viewPos", m_Camera->GetPos());
	m_Shader->SetUniform3f("light1.pos", m_Light.GetPos());
	m_Shader->SetUniform3f("light1.ambient", m_Light.GetAmbi());
	m_Shader->SetUniform3f("light1.diffuse", m_Light.GetDiff());
	m_Shader->SetUniform3f("light1.specular", m_Light.GetSpec());

	for (auto &it: m_Models) {
		it->Draw(m_Shader, true);
		m_Shader->SetUniformMat4("transform", m_Camera->GetProj() * m_Camera->GetView() * it->Transform);
		m_Shader->SetUniformMat4("model", it->Transform);
		m_Shader->SetUniformMat3("inverseModel", glm::mat3(glm::transpose(inverse(it->Transform))));
	}	

	if (m_ColorShader == nullptr)
		return;

	m_ColorShader->Bind();
	m_ColorShader->SetUniform3f("viewPos", m_Camera->GetPos());
	m_ColorShader->SetUniform3f("light1.pos", m_Light.GetPos());
	m_ColorShader->SetUniform3f("light1.ambient", m_Light.GetAmbi());
	m_ColorShader->SetUniform3f("light1.diffuse", m_Light.GetDiff());
	m_ColorShader->SetUniform3f("light1.specular", m_Light.GetSpec());

	for (auto &it: m_Models) {
		it->Draw(m_ColorShader, false);
		m_ColorShader->SetUniformMat4("transform", m_Camera->GetProj() * m_Camera->GetView() * it->Transform);
		m_ColorShader->SetUniformMat4("model", it->Transform);
		m_ColorShader->SetUniformMat3("inverseModel", glm::mat3(glm::transpose(inverse(it->Transform))));
	}	

	m_Models.clear();
}