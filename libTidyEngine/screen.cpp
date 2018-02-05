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
