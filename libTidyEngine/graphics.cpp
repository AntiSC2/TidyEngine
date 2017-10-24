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



#include "graphics.hpp"
#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "renderer.hpp"
#include "screen.hpp"
#include "shader.hpp"

Graphics::Graphics(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor)
{
	Initialize(width, height, title, gl_major, gl_minor);
}

Graphics::~Graphics()
{
	m_Shaders.clear();
}

void Graphics::Initialize(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor)
{
	m_Screen = std::make_unique<Screen>();
	if (!m_Screen->CreateWindow(width, height, title, gl_major, gl_minor))
		throw std::runtime_error("Error: could not create GLFW window");
	if (!m_Screen->InitGL())
		throw std::runtime_error("Error: could not initalize OpenGL");
}

std::string Graphics::GetType()
{
	return "Graphics System";
}

void Graphics::AddRenderer(std::unique_ptr<IRenderer> &&renderer, std::type_index index)
{
	m_Renderers[index] = std::move(renderer);
}

bool Graphics::LoadShaders(std::string name, std::string v, std::string f,
		std::vector<std::string> attributes)
{
	m_Shaders[name] = std::unique_ptr<Shader>(new Shader(v, f));
	if (m_Shaders[name]->InitProgram() == false) {
		printf("Warning: could not initialize shader: %s!\n",
		       name.c_str());
		return false;
	}

	for (size_t i = 0; i < attributes.size(); i++)
		m_Shaders[name]->AddAttribute(attributes[i]);

	if (m_Shaders[name]->LinkProgram() == false) {
		printf("Warning: could not link shader: %s!\n", name.c_str());
		return false;
	}
	
	return true;
}

Shader *Graphics::GetShader(std::string name)
{
	if (m_Shaders.find(name) != m_Shaders.end())
		return m_Shaders[name].get();
	else
		printf("Warning: could not find shader %s\n", name.c_str());
	return nullptr;
}

GLFWwindow *Graphics::GetWindow()
{
	return m_Screen->GetWindow();
}

void Graphics::Execute()
{
	Clear();
	for(auto &it: m_Renderers) {
		it.second->Begin();
		it.second->End();
		it.second->Present();
	}
	Present();
}

void Graphics::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::Present()
{
	glfwSwapBuffers(m_Screen->GetWindow());
}
