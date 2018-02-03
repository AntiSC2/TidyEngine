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
#include <cstdio>
#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "cache.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"
#include "font.hpp"
#include "modelrenderer.hpp"
#include "rect2d.hpp"
#include "screen.hpp"
#include "shader.hpp"
#include "sprite.hpp"
#include "spriterenderer.hpp"

Graphics::Graphics(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor)
{
	Initialize(width, height, title, gl_major, gl_minor);
}

void Graphics::Initialize(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor)
{
	if (!m_Screen.CreateWindow(width, height, title, gl_major, gl_minor))
		throw std::runtime_error("Error: could not create GLFW window");
	if (!m_Screen.InitGL())
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
	return m_Screen.GetWindow();
}

void Graphics::Execute(bool fixed)
{
	if (fixed) {
		for (auto &e: m_Entities)
			e.second->GetComponent<Sprite>().Update();

		return;
	}

	Clear();
	for(auto &r: m_Renderers) {
		auto &rend = r.second;
		if (r.first == std::type_index(typeid(SpriteRenderer))) {
			Rect2D floor = {0.0f, 680.0f, 1280.0f, 720.0f};
			floor.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			rend->SetCamera(&m_EM->GetEntity("Camera").GetComponent<Camera>());
			rend->Begin();
			for (auto &e: m_Entities) {
				Renderable *temp = &e.second->GetComponent<Sprite>();
				temp->Render();
				rend->Draw(temp);
			}
			rend->Draw(&floor);
			rend->DrawText("TidyEngine V0.2", glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), *Res.LoadFont("Acme-Regular.ttf"));
			rend->End();
			rend->Present();
		}
		if (r.first == std::type_index(typeid(ModelRenderer))) {
			auto rend = static_cast<ModelRenderer*>(r.second.get());
			rend->Begin();
			rend->SetCamera(&m_EM->GetEntity("Camera").GetComponent<Camera>());
			rend->Draw(Res.LoadModel("Models/char.obj"));
			Res.LoadModel("Models/char.obj")->Transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
			rend->Draw(Res.LoadModel("Models/wallWindow.fbx"));
			rend->End();
			rend->Present();
		}
	}
	Present();
}

void Graphics::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::Present()
{
	glfwSwapBuffers(m_Screen.GetWindow());
}
