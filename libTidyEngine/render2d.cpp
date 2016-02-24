/*
Copyright (C) 2015 Jakob Sinclair

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

#include "render2d.hpp"

Render2D::Render2D()
{
	;
}

Render2D::~Render2D()
{
	m_Shaders.clear();
}

void Render2D::LoadShaders()
{
	m_Shaders.emplace_back(new Shader);
	m_Shaders[0]->SetSources("shader.vert", "shader.frag");
	if (m_Shaders[0]->InitProgram() == false) {
		return;
	} else if (m_Shaders[0]->LinkProgram() == false) {
		return;
	} else
		m_Shaders[0]->Bind();
}

void Render2D::Begin()
{
	;
}

void Render2D::End()
{
	;
}

void Render2D::Present(GLFWwindow *window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}
