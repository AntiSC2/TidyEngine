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

/* Make sure that glad does
 * not include windows.h
 */
#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include "screen.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow *Screen::m_NeedUpdate = nullptr;

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

bool Screen::NeedUpdate()
{
	if (m_Window == m_NeedUpdate) {
		glfwGetWindowSize(m_Window, (int*)&m_Width, (int*)&m_Height);
		m_NeedUpdate = nullptr;
		return true;
	} else {
		return false;
	}
}

bool Screen::CreateWindow(uint16_t width, uint16_t height, const char* title,
			  int gl_major, int gl_minor)
{
	DestroyWindow();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	if (gl_major == 3 && gl_minor < 2)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	else if (gl_major < 3)
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
	// glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	return true;
}

bool Screen::InitGL()
{
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		printf("Warning: failed to initialize OpenGL context!\n");
		return false;
	}
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("GFX Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	return true;
}

void Screen::CloseWindow()
{
	glfwSetWindowShouldClose(m_Window, GL_TRUE);
}

void Screen::WindowSizeCallback(GLFWwindow *window, int width, int height)
{
	m_NeedUpdate = window;
}

void Screen::DestroyWindow()
{
	if (m_Window != nullptr) {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
}
