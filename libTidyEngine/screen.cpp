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

#include "screen.hpp"

Screen::Screen()
{
        ;
}

Screen::~Screen()
{
        DestroyWindow();
}

uint16_t Screen::GetWidth()
{
	return m_Width;
}

uint16_t Screen::GetHeight()
{
	return m_Height;
}

const char *Screen::GetTitle()
{
	return m_Title;
}

GLFWwindow *Screen::GetWindow()
{
	return m_Window;
}

bool Screen::CreateWindow(uint16_t width, uint16_t height, const char* title,
                          int gl_major, int gl_minor)
{
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
        if (gl_major <= 3 && gl_minor < 2)
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        else
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (m_Window == nullptr) {
                return false;
        } else {
                m_Width = width;
                m_Height = height;
                m_Title = (char*)title;
                glfwMakeContextCurrent(m_Window);
        }
        return true;
}

bool Screen::InitGL()
{
        glewExperimental = GL_TRUE;
        GLenum err;
        err = glewInit();
        if (err != GLEW_OK) {
                printf("Error: %s\n", glewGetErrorString(err));
                return false;
        }
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        return true;
}

void Screen::DestroyWindow()
{
        if (m_Window != nullptr) {
                glfwDestroyWindow(m_Window);
        }
}
