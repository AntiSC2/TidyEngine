/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
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
			//rend->DebugGrid();
			rend->Begin();
			rend->SetCamera(&m_EM->GetEntity("Camera").GetComponent<Camera>());
			rend->Draw(Res.LoadModel("Models/char.obj"));
			Res.LoadModel("Models/char.obj")->Transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
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
