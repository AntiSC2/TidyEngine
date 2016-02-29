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

#include "render2d.hpp"

Render2D::Render2D()
{
	;
}

Render2D::~Render2D()
{
	m_Shaders.clear();
}

void Render2D::LoadShaders(std::string name, std::string v, std::string f,
		std::vector<std::string> attributes)
{
        m_Shaders[name] = std::unique_ptr<Shader>(new Shader(v, f));
        if (m_Shaders[name]->InitProgram() == false) {
                Error e("Exception: could not initialize shader!");
                throw e;
        }

        for (size_t i = 0; i < attributes.size(); i++)
                m_Shaders[name]->AddAttribute(attributes[i]);

        if (m_Shaders[name]->LinkProgram() == false) {
		Error e("Exception: could not link shader!");
                throw e;
	}
}

void Render2D::UseShader(std::string name)
{
	if (m_Shaders.find(name) != m_Shaders.end()) {
		m_Shaders[name]->Bind();
		m_CurrentShader = name;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexUV)); 
	} else {
		printf("Warning: could not find shader %s!\n", name.c_str());
	}
}

void Render2D::StopShaders()
{
	m_Shaders.at(m_CurrentShader)->UnBind();
	m_CurrentShader = "";
}

Batch& Render2D::GetBatch()
{
	return SpriteBatch;
}

void Render2D::Begin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SpriteBatch.Initialise();

}

void Render2D::End()
{
	;
}

void Render2D::Present(GLFWwindow *window)
{
	glfwSwapBuffers(window);
}
