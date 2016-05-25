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

#include "core.hpp"
#include <GLFW/glfw3.h>
#include <FreeImage.h>
#include <al.h>
#include "shader.hpp"
#include "error.hpp"
#include "cache.hpp"
#include "config.hpp"

Core::Core()
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

	FreeImage_Initialise();
	FreeImage_SetOutputMessage(FreeImageError);

	if(m_Screen.CreateWindow(1280, 720, "TidyEngine", 4, 3) != true) {
		printf("Error: glfw could not create window!\n");
		return false;
	} else {
		if (m_Screen.InitGL() == false) {
			printf("Error: could not initialize OpenGL!\n");
			return false;
		}
	}

	try {
		m_Render.LoadShaders("default", "shader.vert", "shader.frag",
		{"position", "color", "uv"});
	}
	catch (std::exception &e) {
		printf("%s", e.what());
		printf("Error: Could not load default texture: default.png\n");
		return false;
	}
	m_DrawSprite.Initialise(m_Render.GetShader("default"),
			&m_Render.GetBatch());
	
	try {
		Resources.CreateTexture("default", "default.png");
	}
	catch (std::exception &e) {
		printf("%s", e.what());
		printf("Error: Could not load default texture: default.png\n");
		return false;
	}
	
	m_Input.Initialise(m_Screen.GetWindow());

	printf("TidyEngine Version: %d.%d\n",
	       TidyEngine_VERSION_MAJOR, TidyEngine_VERSION_MINOR);
	
	return true;
}

void Core::GameLoop()
{
	printf("Main loop was entered.\n");
	while (!glfwWindowShouldClose(m_Screen.GetWindow())) {
		Update();
		DrawGame();
	}
	printf("Main loop was closed.\n");
}

void Core::Quit()
{
	glfwTerminate();
	FreeImage_DeInitialise();
}