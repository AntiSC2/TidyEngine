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
#include <iostream>
#include "core.hpp"
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "audio.hpp"
#include "cache.hpp"
#include "config.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "modelrenderer.hpp"
#include "screen.hpp"
#include "shader.hpp"
#include "spriterenderer.hpp"

void Core::Run() 
{
	if (InitSubSystems() && Init()) {
		GameLoop();
		std::cout << "Fuck!";
		printf("Fuck!");
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
	Graphics *graphics;
	try {
		graphics = &m_EM.CreateSystem<Graphics>((uint16_t)1280, (uint16_t)720, (const char *)"TidyEngine", 4, 3);
		m_EM.CreateSystem<Audio>();
		m_EM.CreateSystem<Input>(graphics->GetWindow());
		graphics->CreateRenderer<SpriteRenderer>();
		graphics->CreateRenderer<ModelRenderer>();
	}
	catch(std::exception &e) {
		printf("%s\n", e.what());
		return false;
	}

	if (graphics->LoadShaders("sprite", "sprite.vert", "sprite.frag",
	   {"position", "color", "uv"}) == false) {
		printf("Error: Failed to load sprite shaders!\n");
		return false;
	}

	if (graphics->LoadShaders("model", "model.vert", "model.frag",
	   {"position", "color", "uv", "normal"}) == false) {
		printf("Error: Failed to load model shaders!\n");
		return false;
	}

	graphics->GetRenderer<SpriteRenderer>().Initialise(graphics->GetShader("sprite"));
	graphics->GetRenderer<ModelRenderer>().Initialise(graphics->GetShader("model"));

	glfwSetWindowSizeCallback(graphics->GetWindow(),
	                          Screen::WindowSizeCallback);

	if (Res.CreateDefaultResources() == false)
		return false;

	printf("TidyEngine Version: %d.%d\n",
	       TidyEngine_VERSION_MAJOR, TidyEngine_VERSION_MINOR);
	
	return true;
}

void Core::GameLoop()
{
	printf("Game loop was entered...\n");

	const double dt = 1.0 / 60.0;
	double current_time = glfwGetTime();
	double accumulator = 0.0;
	double timer = current_time;
	size_t frames = 0;
	size_t updates = 0;

	while (!m_Quit) {
		double new_time = glfwGetTime();
		double frame_time = new_time - current_time;
		current_time = new_time;
		accumulator += frame_time;	
		m_EM.Update();
		while (accumulator > dt) {
			Update(accumulator);
			accumulator -= dt;
			updates++;
		}

		frames++;

		if (current_time - timer > 1.0) {
			printf("Updates: %llu\nFPS: %llu\n", updates, frames);
			timer = current_time;
			updates = 0;
			frames = 0;
		}

		if (glfwWindowShouldClose(m_EM.GetSystem<Graphics>().GetWindow()) == true)
			m_Quit = true;
	}
	printf("Game loop was closed...\n");
}

void Core::Quit()
{
	printf("1");
	Res.Clean();
	FT_Done_FreeType(m_FontLib);
	glfwTerminate();
	printf("2");
}
