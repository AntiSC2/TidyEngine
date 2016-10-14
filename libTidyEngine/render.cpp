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

#include "render.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "shader.hpp"

Render::Render()
{
	;
}

Render::~Render()
{
	m_Shaders.clear();
}

bool Render::LoadShaders(std::string name, std::string v, std::string f,
		std::vector<std::string> attributes)
{
	m_Shaders[name] = std::unique_ptr<Shader>(new Shader(v, f));
	if (m_Shaders[name]->InitProgram() == false) {
		printf("Warning: could not initialize shader!");
		return false;
	}

	for (size_t i = 0; i < attributes.size(); i++)
		m_Shaders[name]->AddAttribute(attributes[i]);

	if (m_Shaders[name]->LinkProgram() == false) {
		printf("Warning: could not link shader!");
		return false;
	}
}

Shader *Render::GetShader(std::string name)
{
	if (m_Shaders.find(name) != m_Shaders.end())
		return m_Shaders[name].get();
	else
		std::printf("Warning: could not find shader %s!\n",
				name.c_str());
	return nullptr;
}

Batch &Render::GetBatch()
{
	return m_Batch;
}

void Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::Present(GLFWwindow *window)
{
	glfwSwapBuffers(window);
}