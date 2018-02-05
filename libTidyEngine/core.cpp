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
	}
	Quit();
}

bool Core::InitSubSystems()
{
	if (glfwInit() == GL_FALSE)
		return false;

	int error = FT_Init_FreeType(&Res.m_FontLib);
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

	if (graphics->LoadShaders("model-texture", "model-texture.vert", "model-texture.frag",
	   {"position", "color", "uv", "normal"}) == false) {
		printf("Error: Failed to load model-texture shaders!\n");
		return false;
	}

	if (graphics->LoadShaders("model-color", "model-color.vert", "model-color.frag",
	   {"position", "color", "normal"}) == false) {
		printf("Error: Failed to load model-color shaders!\n");
		return false;
	}

	if (graphics->LoadShaders("grid", "grid.vert", "grid.frag", {}) == false) {
		printf("Error: Failed to load grid shaders!\n");
		return false;
	}

	graphics->GetRenderer<SpriteRenderer>().Initialise(graphics->GetShader("sprite"));
	graphics->GetRenderer<ModelRenderer>().Initialise(graphics->GetShader("model-texture"), graphics->GetShader("model-color"), graphics->GetShader("grid"));

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
	Res.Clean();
	FT_Done_FreeType(Res.m_FontLib);
	m_EM.RemoveSystem<Graphics>();
	glfwTerminate();
}
