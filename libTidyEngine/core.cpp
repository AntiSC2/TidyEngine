/*
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
*/

#include "core.hpp"

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
