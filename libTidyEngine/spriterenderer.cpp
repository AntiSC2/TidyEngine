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
#define SPRITE_COUNT 500000
#include "spriterenderer.hpp"
#include "shader.hpp"
#include "camera.hpp"

SpriteRenderer::SpriteRenderer()
{
	;
}

SpriteRenderer::~SpriteRenderer()
{
	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
}

void SpriteRenderer::Update(double delta)
{
	;
}

void SpriteRenderer::Initialise(Shader *shader)
{
	m_Shader = shader;

	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
	
	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * SPRITE_COUNT * 6, NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex),
			(void*)offsetof(Vertex, Color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, TexUV));

	glBindVertexArray(0);
}

void SpriteRenderer::Present(const Camera &camera)
{
	m_Shader->SetUniformMat4("transform", camera.GetProj() * camera.GetView() * camera.GetModel());

	glBindVertexArray(m_VAOID);
	for (size_t i = 0; i < m_RenderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].Tex);
		glDrawArrays(GL_TRIANGLES, (GLsizei)m_RenderBatches[i].Offset,
		            (GLsizei)m_RenderBatches[i].Vertices);
	}
}