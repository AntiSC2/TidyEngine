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
	if(InitSubSystems() && Init()) {
		GameLoop();
	}
	Quit();
}

bool Core::InitSubSystems()
{
    	bool success = true;
        if (glfwInit() == GL_FALSE) {
                success = false;
        }
        FreeImage_Initialise();
        FreeImage_SetOutputMessage(FreeImageError);

	if(m_Screen.CreateWindow(1280, 720, "TidyEngine", 3, 3) != true) {
		success = false;
                printf("Error: glfw could not create window!\n");
        } else {
                if (m_Screen.InitGL() == false) {
                        printf("Error: could not initialize OpenGL!\n");
                        success = false;
                }
        
        }

        m_2DRender.LoadShaders("default", "shader.vert", "shader.frag",
        {"position", "color", "uv"});
        m_2DRender.GetShader("default")->Bind();

        m_DrawSprite.Initialise(m_2DRender.GetShader("default"),
                        &m_2DRender.GetBatch());
	
        Resources.CreateTexture("default", "default.png");
        
        m_Input.Initialise(m_Screen.GetWindow());

        printf("TidyEngine Version: %d.%d\n",
               TidyEngine_VERSION_MAJOR, TidyEngine_VERSION_MINOR);
	
	return success;
}

void Core::GameLoop()
{
	printf("Main loop was entered.\n");
	m_Screen.GetWidth();
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
