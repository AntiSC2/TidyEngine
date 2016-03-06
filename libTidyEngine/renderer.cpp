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

#include "renderer.hpp"
#include "shader.hpp"
#include "batch.hpp"
#include "renderable.hpp"

Renderer::Renderer()
{
	;
}

Renderer::~Renderer()
{
	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
}

void Renderer::Begin()
{
	m_Shader->Bind();
	m_Batch->Begin(m_VAOID, m_VBOID);
}

void Renderer::Draw(const Renderable &object)
{
	m_Batch->Draw(object);
}

void Renderer::End()
{
	m_Batch->End();
}

void Renderer::Present()
{
	m_Batch->Present();
}
