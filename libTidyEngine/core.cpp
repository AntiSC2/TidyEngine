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

#include "core.hpp"
#include <GLFW/glfw3.h>
#include <FreeImage.h>
#include <al.h>
#include "shader.hpp"
#include "error.hpp"
#include "cache.hpp"
#include "config.hpp"

Core::Core() : m_Audio(true)
{
	;
}

Core::~Core()
{
	;
}

void Core::Run() 
{
	if (InitSubSystems() && Init()) {
		GameLoop();
	}
	Quit();
}

bool Core::InitSubSystems()
{
	if (glfwInit() == GL_FALSE)
		return false;

	int error = FT_Init_FreeType(&m_FontLib);
	if (error) {
		printf("Error: Could not initialize Freetype2!\n");
		return false;
	}

	FreeImage_Initialise();
	FreeImage_SetOutputMessage(FreeImageError);

	if (m_Screen.CreateWindow(1280, 720, "TidyEngine", 4, 3) != true) {
		printf("Error: glfw could not create window!\n");
		return false;
	} else {
		if (m_Screen.InitGL() == false) {
			printf("Error: could not initialize OpenGL!\n");
			return false;
		}
	}

	if (m_Graphics.LoadShaders("sprite", "sprite.vert", "sprite.frag",
	   {"position", "color", "uv"}) == false) {
		printf("Error: Failed to load sprite shaders!\n");
		return false;
	}

	if (m_Graphics.LoadShaders("model", "model.vert", "model.frag",
	   {"position", "color", "uv", "normal"}) == false) {
		printf("Error: Failed to load model shaders!\n");
		return false;
	}

	m_SpriteRenderer.Initialise(m_Graphics.GetShader("sprite"));
	m_ModelRenderer.Initialise(m_Graphics.GetShader("model"));

	glfwSetWindowSizeCallback(m_Screen.GetWindow(),
	                          Screen::WindowSizeCallback);
	m_Input.Initialise(m_Screen.GetWindow());
	m_Audio.CreateSystem();

	if (Resources.CreateDefaultResources() == false)
		return false;

	printf("TidyEngine Version: %d.%d\n",
	       TidyEngine_VERSION_MAJOR, TidyEngine_VERSION_MINOR);
	
	return true;
}

void Core::GameLoop()
{
	printf("Game loop was entered.\n");

	const double dt = 1.0 / 60.0;
	double current_time = glfwGetTime();
	double accumulator = 0.0;
	double timer = current_time;
	size_t frames = 0;
	size_t updates = 0;

	while (!glfwWindowShouldClose(m_Screen.GetWindow())) {
		double new_time = glfwGetTime();
		double frame_time = new_time - current_time;
		current_time = new_time;
		accumulator += frame_time;	

		while (accumulator > dt) {
			Update(accumulator);
			accumulator -= dt;
			updates++;
		}

		DrawGame();
		m_Input.Update();
		frames++;

		if (current_time - timer > 1.0) {
			printf("Updates: %llu\nFPS: %llu\n", updates, frames);
			timer = current_time;
			updates = 0;
			frames = 0;
		}
	}
	printf("Game loop was closed.\n");
}

void Core::Quit()
{
	Resources.Clean();
	FT_Done_FreeType(m_FontLib);
	m_Audio.DestroySystem();
	glfwTerminate();
	FreeImage_DeInitialise();
}
